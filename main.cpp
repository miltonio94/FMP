#include <SFML/Graphics.hpp>
#include <sstream>
#include "/RtMidi.h"
#include <signal.h>
#include <cstdlib>
#include <iostream>



#define N_WHITE 36
#define N_BLACK 25

using namespace sf;


// RectangleShape* generatePiano(int nWhiteKeys, int nBlackKeys, Vector2f resolution);
void generatePiano(RectangleShape piano[], int nWhiteKeys, int nBlackKeys, Vector2f resolution);
bool isKeySharp(int key);

bool done;

static void finish(int ignore){ done = true; }

RtMidiIn *midiIn = new RtMidiIn();
std::vector<unsigned char> message;
int nBytes;
double stamp;
RectangleShape piano[N_WHITE + N_BLACK];

int main(int, char const**)
{

    std::cout << "Hello" << std::endl;
    // unsigned int nPorts = midiIn->getPortCount();
    // if ( nPorts == 0 ) {
    //     std::cout << "No ports available!\n";
    // } else{
    //     midiIn->openPort(0);
    //     // Don't ignore sysex, timing, or active sensing messages.
    //     midiIn->ignoreTypes( false, false, false );

    //     std::cout << "Reading MIDI from port...\n";
    // }

    

    done = false;
    (void) signal(SIGINT, finish);

    

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
    // Create the main window
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Piano Key Generator",Style::Default);

    
    generatePiano(piano, N_WHITE, N_BLACK, resolution);
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        if(!done){
            // stamp = midiIn->getMessage( &message );
            nBytes = message.size();
            for (int i=0; i<nBytes; i++ ){
                std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
            }
            if ( nBytes > 0 ){
                std::cout << "stamp = " << stamp << std::endl;
            }
        }
        // Clear screen
        window.clear();

        RectangleShape shape;
        shape.setPosition(0,0);
        shape.setSize(resolution);
        shape.setFillColor(Color::Cyan);
        window.draw(shape);

        for(int i = 0; i < N_WHITE + N_BLACK; i++){
            if(!isKeySharp(i)){
                window.draw(piano[i]);
            }
        }
        for(int i = 0; i < N_WHITE + N_BLACK; i++){
            if(isKeySharp(i)){
                window.draw(piano[i]);
            }
        }


        
//        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}

bool isKeySharp(int key){
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

void generatePiano(RectangleShape piano[], int nWhiteKeys, int nBlackKeys, Vector2f resolution){
    int nKeys = nWhiteKeys + nBlackKeys;    

    Vector2f whiteKey = Vector2f(resolution.x / nWhiteKeys, resolution.y / 6);

    Vector2f blackKey = Vector2f(whiteKey.x * .5, whiteKey.y * .65);


    float yPos = resolution.y - whiteKey.y;
    float x = 0.0;

    for(int i = 0; i < nKeys; i++){
        if(isKeySharp(i)){
            float xOrigin = blackKey.x * .5;
            piano[i].setSize(blackKey);
            piano[i].setOrigin(xOrigin, 0);
            piano[i].setPosition(Vector2f(x * whiteKey.x, yPos + 5));

            piano[i].setFillColor(Color::Black);
            piano[i].setOutlineColor(Color::White);
            piano[i].setOutlineThickness(5);
        } else{
            piano[i].setSize(whiteKey);
            piano[i].setPosition(Vector2f(x * whiteKey.x, yPos));
            piano[i].setFillColor(Color::White);
            piano[i].setOutlineColor(Color::Black);
            piano[i].setOutlineThickness(5);
            x++;
        }
    }

}

