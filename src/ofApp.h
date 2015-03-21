#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"
#include "wiringPi.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void gotMessage(ofMessage msg);
    
    void onGifSaved(string & fileName);
    void captureFrametoGif();

    void saveOverlay();
    void saveGif();

    void readButtonState();
    
    

    

   
    
    ofVideoGrabber      vidGrabber;
    ofxGifEncoder gifEncoder;
        
    int gifFrameCounter;
    
    vector<ofImage> images;
    vector<ofPoint> lightPoints;
    vector<ofPoint> darkPoints;
    
    bool bGifMode;
    bool bSingleMode;
    bool bRecording;

    int buttonTimer;
    int timer;

    int buttonPin;
    int LEDpin;


    
    
    
		
};
