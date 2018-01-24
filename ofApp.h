#pragma once
#include "ofMain.h"
#include "ofFbo.h"

#include "opencv2/opencv.hpp"

#include "Particle.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	ofFbo fbo;

	cv::VideoCapture cap;
	cv::Size cap_size;

	cv::Mat frame;
	ofImage image;

	vector<unique_ptr<Particle>> particles;
};