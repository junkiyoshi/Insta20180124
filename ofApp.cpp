#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackground(0);
	ofSetWindowTitle("Insta");

	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->cap.open(1);

	this->cap_size = cv::Size(this->cap.get(CV_CAP_PROP_FRAME_WIDTH), this->cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	ofSetFrameRate(this->cap.get(CV_CAP_PROP_FPS));

	this->image.allocate(this->cap_size.width, this->cap_size.height, OF_IMAGE_GRAYSCALE);
	this->frame = cv::Mat(this->image.getHeight(), this->image.getWidth(), CV_MAKETYPE(CV_8UC1, this->image.getPixels().getNumChannels()), this->image.getPixels().getData(), 0);

	for (int i = 0; i < 2048; i++) {

		unique_ptr<Particle> particle(new Particle());
		this->particles.push_back(std::move(particle));
	}

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
	
	cv::Mat src;
	this->cap >> src;
	if (src.empty()) { 

		return;
	}
	cv::Canny(src, this->frame, 50, 200);
	cv::flip(this->frame, this->frame, 1);

	vector<ofVec2f> edges;
	for (int y = 0; y < this->frame.rows; y += 3) {

		for (int x = 0; x < this->frame.cols; x += 3) {

			if (this->frame.at<unsigned char>(y, x) > 0) {

				edges.push_back(ofVec2f(x, y));
			}
		}
	}

	this->fbo.begin();
	ofClear(0);

	for (int i = 0; i < this->particles.size(); i++) {

		this->particles[i]->update();

		for (ofVec2f edge : edges) {

			float distance = this->particles[i]->get_location().distance(edge);
			if (distance < 30) {

				ofSetColor(this->particles[i]->get_body_color(), ofMap(distance, 0, 30, 255, 0));
				ofDrawLine(this->particles[i]->get_location(), edge);
			}
		}
	}
	

	//this->image.update();
	//this->image.draw(0, 0);

	this->fbo.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->fbo.draw(0, 0);
}

//========================================================================
int main() {

	ofSetupOpenGL(640, 480, OF_WINDOW);
	ofRunApp(new ofApp());
}