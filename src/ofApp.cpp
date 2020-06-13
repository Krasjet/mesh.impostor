#include "ofApp.h"
#include "ofxMeshGen.h"
#include "noise.h"

void ofApp::setup()
{
  ofSetFrameRate(60);

  cam.setPosition(glm::vec3(CAM_COORD));
  cam.lookAt({0, 0, 0});

  dark = true;
  bgDark = true;
  amplitude = 1;

  impostor = makeKST3(50);
  subdivideMesh(impostor, 6);

  mesh = makeCube(50);
  subdivideMesh(mesh, 6);
}

void ofApp::update()
{
  for (size_t i = 0; i < std::min(mesh.getNumVertices(), impostor.getNumVertices()); ++i) {
    const ofVec3f &normal = impostor.getNormal(i), pos = impostor.getVertex(i);
    float scaling = amplitude * step4d(0.1f * pos.x, 0.1f * pos.y, 0.1f * pos.z, ofGetElapsedTimef());
    mesh.setVertex(i, pos + scaling * normal);
  }
  recalcNormals(mesh);
}

void ofApp::draw()
{
  ofBackground(ofFloatColor(bgDark ? 0 : 1));

  ofEnableDepthTest();

  ofPushMatrix();
  cam.begin();

  ofSetColor(ofFloatColor(dark ? 0 : 1));
  mesh.drawFaces();

  ofSetColor(ofFloatColor(dark ? 1 : 0));
  ofSetLineWidth(1.5);
  mesh.drawWireframe();

  cam.end();

  ofPopMatrix();
  ofDisableDepthTest();
}

void ofApp::keyPressed(int key)
{
  switch (key) {
    case 'x':
      screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
      screenshot.save("screenshot_" + ofGetTimestampString() + ".png");
      break;
    case '+':
      amplitude += 0.1;
      break;
    case '=':
      amplitude = 0;
      break;
    case '-':
      amplitude -= 0.1;
      break;
    case 'd':
      dark = !dark;
      break;
    case 'D':
      bgDark = !bgDark;
      break;
    case '0':
      cam.setPosition(glm::vec3(CAM_COORD));
      cam.lookAt({0, 0, 0});
      break;
    case '1':
      cam.setPosition(glm::vec3(CAM_COORD) / 1.3);
      cam.lookAt({0, 0, 0});
      break;
    case '2':
      cam.setPosition(glm::vec3(CAM_COORD));
      cam.move(0, -35, 0);
      cam.rotateAroundDeg(-15, {0, 1, 0}, {0, 0, 0});
      cam.lookAt({0, 0, 0});
      break;
    default:
      break;
  }
};

int main()
{
  ofSetupOpenGL(1000, 1000, OF_WINDOW);
  ofRunApp(new ofApp());
}
