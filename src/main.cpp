#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

struct Key{

};

Key[56] generatePiano();

int main(){
    VideoMode vm(1920,1200);
    RenderWindow window(vm, "Piano Key Generator", Style::Fullscreen);
    

    while(window.isOpen()){
        /*
        *       Input Handling
        */

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){
            window.close();
        }

        /*
        *       Update
        */


       /*
        *       Draw 
        */
    }
}