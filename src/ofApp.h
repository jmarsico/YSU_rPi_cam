#pragma once

#include "ofMain.h"
#include "ofxGifEncoder.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
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
    
    
    
		
};
