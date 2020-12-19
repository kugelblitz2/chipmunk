#include "keyboard.h"

bool keyboard::isChipKey(char key){
    bool isKey = false;
    for(int i = 0; i < 16; i++){        // Checks given character with the list of CHIP-8 keys defined in config.h
        if(key == chipKey[i]){
            isKey = true;
            break;
        }
    }
    return isKey;
}

#if defined(_WIN32) || defined(_WIN32)  // NT optimized implementation
#include <winuser.h>

bool keyboard::isPressed(char key) {
    short keyStatus = GetKeyState((int)chipKey[key]);
    bool pressed = keyStatus >> 6;
    if(pressed) return true;
    else return false;
}

// #elif defined(__APPLE__)                // OS X optimized implementation

// #elif defined(__linux__)                // GNU/Linux optimized implemention

#else                                   // Generic ncurses implementation that doesn't handle multiple simultaneous keypresses

bool keyboard::isPressed(char key) {
    int kPressed = getch();
    if(chipKey[key] == kPressed) return true;
    else return false;
}

#endif

char keyboard::readKey(){
    int key = getch();
    if (key == -1) return 255;          // Returns 255 if no key is being pressed
    if(!isChipKey(key)) return 255;     // Checks if the key pressed is mapped to a CHIP-8 key
    else return keyChip[key];           // If so, return the corresponding CHIP-8 key
}