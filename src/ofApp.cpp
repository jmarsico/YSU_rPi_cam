#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    frameCounter = 0;
    
    ofSetFrameRate(30);

    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(640, 480);

    gifEncoder.setup(vidGrabber.getWidth(), vidGrabber.getHeight(), .25, 256);
    ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
    
//    fileName = "/mnt/storage/rpitest";
    
    ofSetWindowShape(vidGrabber.getWidth(), vidGrabber.getHeight()	);
    
    bRecording = false;

    ofEnableAlphaBlending();
    timer = 0;
    
    
    bGifMode = false;
    bSingleMode = false;
    
    gifFrameCounter = 0;
}

void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::update(){
    
    //update the video camera
    vidGrabber.update();

    //if there is a new frame and we are recording...
    if(vidGrabber.isFrameNew() && bRecording)
    {

        if(timer % 15 == 0)
        {
            ofImage i;
            i.setFromPixels(vidGrabber.getPixelsRef());
           
            images.push_back(i);
            
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
            
            ofLog() << "capture, new size: " << images.size();
        }
        
        
        
    }
    
    
   
    
    ofLog() << "timer: " << timer;
    
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
        if(images.size() >= 10)
        {
            saveOverlay();
        }
    }
    
    timer ++;
    if(!bRecording) timer = 0;
    

}

//--------------------------------------------------------------
void ofApp::captureFrametoGif() {
    
    ofImage p;
    p.allocate(vidGrabber.getWidth(), vidGrabber.getHeight(), OF_IMAGE_COLOR_ALPHA);
    p.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    

    
    gifEncoder.addFrame(p);
    gifFrameCounter ++;
    
    if(gifFrameCounter > 9)
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
    bRecording = false;
    images.clear();
    lightPoints.clear();
    darkPoints.clear();
    frameCounter = 0;
    
}


//--------------------------------------------------------------
void ofApp::onGifSaved(string &fileName) {
    cout << "gif saved as " << fileName << endl;
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
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
