#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetBackgroundColor(251,183,49);

    midiIn.listInPorts(); // dumping all ports to console
    midiIn.openPort(0);
    
    // don't ignore sysex, timing, & active sense messages, <==== not sure what these are, taken out from the example code without understanding it
    // these are ignored by default
    midiIn.ignoreTypes(false,false,false);
    
    midiIn.addListener(this); // adding the ofApp as a listener
    
    midiIn.setVerbose(true); // printing received messages to console.
    
    generatePiano(NUMB_WHITE_KEYS + NUMB_BLACK_KEYS);
    
    
    ofSetLineWidth(3.75);

}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(int i = 0; i < NUMB_WHITE_KEYS + NUMB_BLACK_KEYS; i++){
        if(!piano[i].isSharp){
            ofSetRectMode(OF_RECTMODE_CORNER);
            drawKey(piano[i].x, piano[i].y, piano[i].width, piano[i].height, piano[i].colour, piano[i].pressed);
        }
    }
    for(int i = 0; i < NUMB_WHITE_KEYS + NUMB_BLACK_KEYS; i++){
        if(piano[i].isSharp){
            ofSetRectMode(OF_RECTMODE_CENTER);
            drawKey(piano[i].x, piano[i].y, piano[i].width, piano[i].height, piano[i].colour, piano[i].pressed);
        }
    }
//    if(piano[i].isSharp){
//        ofSetRectMode(OF_RECTMODE_CENTER);
//    } else{
//        ofSetRectMode(OF_RECTMODE_CORNER);
//    }
}

//--------------------------------------------------------------
void ofApp::drawKey(float x, float y, int w, int h, ofColor colour, bool pressed){
//    RGB(20,107,62) RGB(40,151,91)
//    RGB(130,112,213) moody blues
    if(pressed && colour == ofColor(0)){
        colour = ofColor(130,112, 213);
    } else if(pressed && colour == ofColor(255)){
        colour = ofColor(40,151,91);
    }
    
    ofSetColor(colour);
    ofFill();
    ofDrawRectangle(x, y, w, h);
    
    ofNoFill();
    ofSetColor(0);
    ofDrawRectangle(x, y, w, h);
}

//--------------------------------------------------------------
void ofApp::generatePiano(char firstKey, char lastKey, int keysAmount){
    
}

bool ofApp::isKeySharp(int key){
    bool retVal = false;
    
    switch (key % 12) {
        case 1:
            retVal = true;
            break;
        case 3:
            retVal = true;
            break;
        case 6:
            retVal = true;
            break;
        case 8:
            retVal = true;
            break;
        case 10:
            retVal = true;
            break;
        default:
            retVal = false;
            break;
    }
    
    return retVal;
}

//--------------------------------------------------------------
void ofApp::generatePiano(int keysAmount){
    float width = ofGetWidth() / NUMB_WHITE_KEYS;
    float height = ofGetHeight() / 6;
    int y =  ofGetHeight() - height;
    
    for(int i = 0, x = 0; i < keysAmount; i++){
        if(isKeySharp(i)){
            piano[i].width = width * .5;
            piano[i].height = height * .65;
            piano[i].isSharp = true;
            
            piano[i].x = x * width;
            piano[i].y = y + (height * .65) / 2.;
            piano[i].colour = ofColor(0);
        } else{
            piano[i].width = width;
            piano[i].height = height;
            
            
            piano[i].x = x * width + 1.;
            piano[i].y = y;
            piano[i].colour = ofColor(255);
            x++;
        }
        piano[i].number = i + 36;
    }
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg){
    
    midiMsg = msg;
    
    
    piano[msg.pitch - 36].pressed =  msg.status == 144;
    
    
    
    
    
    cout << "stat: " << midiMsg.status << "\n"
    << "chan: " << midiMsg.channel << "\n"
    << "control: " << midiMsg.control << "\n"
    << "val: " << midiMsg.value << "\n"
    << "pitch: " << midiMsg.pitch << "\n"
    << "vel: " << midiMsg.velocity << endl;
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    // cleaniong up things
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}


