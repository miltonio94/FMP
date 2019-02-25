#pragma once

#define KEY_DOWN 144
#define KEY_UP 128

#define NUMB_WHITE_KEYS  44//36
#define NUMB_BLACK_KEYS  33//25

#include "ofMain.h"
#include "ofxMidi.h"

struct Key {
    char note;
    int number;
    bool isSharp;
    bool pressed;
    
    int width;
    int height;
    float x;
    float y;
    ofColor colour;
};

class ofApp : public ofBaseApp, public ofxMidiListener {
        Key piano[NUMB_WHITE_KEYS + NUMB_BLACK_KEYS];
        ofxMidiIn midiIn;
        ofxMidiMessage midiMsg;
        std::size_t maxMsgs = 10;
    
    void generatePiano(char firstKey, char lastKey, int keysAmount);
    void generatePiano(int keysAmount);
    void drawKey(float x, float y, int w, int h, ofColor colour, bool pressed);
//    void drawKey(float x, float y, int w, int h, int colour, bool pressed);
    bool isKeySharp(int key);
    
    
	public:
		void setup();
		void update();
		void draw();
    
        void exit();
    
        void newMidiMessage(ofxMidiMessage& msg);
    
		void windowResized(int w, int h);
	
		
};

