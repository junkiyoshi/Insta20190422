#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 3);
	auto& triangles = ico_sphere.getMesh().getUniqueFaces();
	for (auto& triangle : triangles) {
		
		glm::vec3 loc = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		this->locations.push_back(loc);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofFill();
	ofSetColor(239);
	ofDrawSphere(298);

	ofFill();
	ofSetColor(39);

	vector<glm::vec3> tmp_locations;
	for(int i = 0; i < this->locations.size(); i++){

		auto tmp_location = locations[i];
		float noise_value = ofNoise(locations[i].x * 0.005, locations[i].y * 0.005, locations[i].z * 0.005, ofGetFrameNum() * 0.008);
		if (noise_value > 0.65) {

			tmp_location *= ofMap(noise_value, 0.65, 1.0, 1.0, 1.35);
		}
		
		tmp_locations.push_back(tmp_location);
	}

	for(int i = 0; i < tmp_locations.size(); i++){

		ofDrawSphere(tmp_locations[i], 3);
		for (int k = i + 1; k < tmp_locations.size(); k++){

			if (glm::distance(tmp_locations[i], tmp_locations[k]) < 30) {

				ofDrawLine(tmp_locations[i], tmp_locations[k]);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}