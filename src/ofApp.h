#pragma once

#define WEBCAM

#include "ofMain.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    void init();

    ofShader shader;

    ofImage emptyImage;
    ofFbo fbo, joinedImageFbo;

    int numImages, numCrop, windowW, windowH, textureW, textureH;
    ofDirectory dir;
    vector<ofImage> images;
    vector<float> periodicTime;
    vector<int> imageIds, nextImageIds, opacity, elapsedTime, elapsedTimePre;
};
