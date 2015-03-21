#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(30);

    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640, 480);
    ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight() );

    gifEncoder.setup(vidGrabber.getWidth(), vidGrabber.getHeight(), .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
    
    ofEnableAlphaBlending();
   
    wiringPiSetup();
    buttonPin = 7;
    pinMode(buttonPin, INPUT);
    pullUpDnControl(buttonPin, PUD_UP);

    LEDpin = 2;
    pinMode(LEDpin, OUTPUT);
    
    timer = 0;
        
    bGifMode = false;
    bSingleMode = false;
    bRecording = false;
    
    gifFrameCounter = 0;
    buttonTimer = 0;
}


//--------------------------------------------------------------
void ofApp::update(){
    
    //update the video camera
    vidGrabber.update();

    //if there is a new frame and we are recording...
    if(vidGrabber.isFrameNew() && bRecording)
    {

        //every 15 frames of video do this stuff
        if(timer % 15 == 0)
        {
            //get a new ofImage object from the video
            ofImage i;
            i.setFromPixels(vidGrabber.getPixelsRef());
           
            //add the image object to the queue
            images.push_back(i);
            digitalWrite(LEDpin, LOW);
            ofSleepMillis(100);
            digitalWrite(LEDpin, HIGH);

            //tell us how many images we have
            ofLog() << "CAPTURE, we now have " << images.size() << " images.";
            

            int brightest = 0;
            int darkest = 255;
            
            for(int x = 0; x < vidGrabber.getWidth(); x++)
            {
                for(int y = 0; y < vidGrabber.getHeight(); y++)
                {
                    
                    int currentBrightness = i.getPixelsRef().getColor(x, y).getBrightness();
                    
                    if( currentBrightness > brightest)
                    {
                        
                        brightest = currentBrightness;
                        ofPoint brightPoint;
                        brightPoint.set(x,y);
                        lightPoints.push_back(brightPoint);
                        
                    }
                    
                    if(currentBrightness < darkest)
                    {
                        darkest = currentBrightness;
                        ofPoint darkPoint;
                        darkPoint.set(x, y);
                        darkPoints.push_back(darkPoint);
                    }
                }
            } 
        }

        timer ++;
           
    }
    if(!bRecording) timer = 0;  
    // ofLog() << "timer: " << timer;  

    readButtonState();
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255, 255, 255);
    
    float xInc = ofGetWidth()/3;
    float yInc = ofGetHeight()/3;
    
    
    if(images.size() > 0){
        
        for(int i = 0; i < images.size(); i++)
        {
            
            
            ofSetColor(255, 255/9);
            images[i].draw(0, 0);
        }
    }
    
    ofPolyline lightShape;
    //draw the brightness
    ofSetPolyMode(OF_POLY_WINDING_NEGATIVE);
    ofFill();
    
    for(int i = 0; i < lightPoints.size(); i++)
    {
        float x,y;
        x = i % 3;
        y = floor(i/3);
        lightShape.addVertex(lightPoints[i].x + x*640/3, lightPoints[i].y + y*480/3);
        //ofVertex(lightPoints[i].x + x*640, lightPoints[i].y + y*480);
    }
    lightShape.close();
    
    lightShape.draw();
//    ofEndShape();
    
    ofPolyline darkShape;
    //draw the brightness
    //ofSetPolyMode(OF_POLY_WINDING_ODD);
    
    ofFill();
    ofSetPolyMode(OF_POLY_WINDING_NEGATIVE);
    for(int i = 0; i < darkPoints.size(); i++)
    {
        float x,y;
        x = i % 3;
        y = floor(i/3);
        darkShape.addVertex(darkPoints[i].x + x*640/3, darkPoints[i].y + y*480/3);
        //ofVertex(lightPoints[i].x + x*640, lightPoints[i].y + y*480);
    }
    
    darkShape.close();
    ofSetColor(0, 50);
    darkShape.draw();
    
    if(bGifMode)
    {
        if(timer % 15 == 0)
        {
            captureFrametoGif();
        }
    }
    
    if(bSingleMode)
    {
        if(images.size() >= 9)
        {
            saveOverlay();
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::captureFrametoGif() {
    
    ofImage p;
    p.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), OF_IMAGE_COLOR_ALPHA);
    p.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    

    
    gifEncoder.addFrame(p);
    gifFrameCounter ++;
    digitalWrite(LEDpin, LOW);
    ofSleepMillis(100);
    digitalWrite(LEDpin, HIGH);
    
    if(gifFrameCounter >= 9)
    {
        saveGif();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::saveGif(){
    bRecording = false;
    bGifMode = false;
    string fileName = ofGetTimestampString("%Y_%n_%d_%H_%M_%S");
    fileName.append(".gif");
    gifEncoder.save(fileName);
    images.clear();
    lightPoints.clear();
    darkPoints.clear();
    gifFrameCounter = 0;

    ofLog() << "gif save started";
    

    //    fileName = "/mnt/storage/rpitest";
}


//--------------------------------------------------------------
void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
    digitalWrite(LEDpin, LOW);
}


//--------------------------------------------------------------
void ofApp::saveOverlay(){
    string fileName = ofGetTimestampString("%Y_%n_%d_%H_%M_%S");
    fileName.append(".png");
    ofSaveScreen(fileName);
    
    images.clear();
    lightPoints.clear();
    darkPoints.clear();
    
    bRecording = false;
    bSingleMode = false;

    ofLog() << "Save Overlay done";
    digitalWrite(LEDpin, LOW);
    

    //    fileName = "/mnt/storage/rpitest";
}



//--------------------------------------------------------------
void ofApp::readButtonState(){
    if(digitalRead(buttonPin) == LOW)
    {
        buttonTimer++;
    } else if(digitalRead(buttonPin) == HIGH)
    {
        if(buttonTimer > 5  &&  buttonTimer < 30)
        {
            ofLog() << "*********************************** SMALL";
            bRecording = !bRecording;
            bSingleMode = true;
            digitalWrite(LEDpin, HIGH);
        }
        if(buttonTimer > 30)
        {
            ofLog() << "***********************************LONG";
            bRecording = !bRecording;
            bGifMode = true;
            digitalWrite(LEDpin, HIGH);
        }

        buttonTimer = 0;

    }

    ofLog() << "buttonTimer: " << buttonTimer;

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='r')
    {
        bRecording = !bRecording;
        bSingleMode = true;
        
    }
    
    if(key=='g')
    {
        bRecording = !bRecording;
        bGifMode = true;
    }
    
    if(key=='c')
    {
        saveGif();
    }
}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}


//--------------------------------------------------------------
void ofApp::exit() {

}