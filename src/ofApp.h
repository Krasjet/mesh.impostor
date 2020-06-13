#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

  ofEasyCam cam;

  ofMesh mesh;
  ofMesh impostor;

  float amplitude;
  bool dark;
  bool bgDark;
  const float CAM_COORD = 150 / sqrt(3);

  ofImage screenshot;
};
