#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "wiringPi.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void gotMessage(ofMessage msg);
    

    void onGifSaved(string & fileName);
    void captureFrametoGif();
    
    
    
    
    void saveOverlay();
    void saveGif();
    
    void exit();

    
    int gifFrameCounter;
    
    ofVideoGrabber      vidGrabber;
    ofxGifEncoder gifEncoder;
    bool bRecording;
    int sampleRate;
    int channels;
    
    int frameCounter;
    
    ofFbo fbo;
    ofImage image;
    ofPixels pix;
    
    
    int timer;
    
    vector<ofImage> images;
    
    vector<ofPoint> lightPoints;
    vector<ofPoint> darkPoints;
    
    bool bGifMode;
    bool bSingleMode;

    bool buttonTimer;
    
    
    
		
};
