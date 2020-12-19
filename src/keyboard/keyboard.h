#ifndef KEYBOARD_H
#define KEYBOARD_H
#include "../config.h"
#include "../system/chip8.h"

class keyboard {
    public:
    bool isChipKey(char key);       // Checks if a given key is mapped to a CHIP-8 key
    bool isPressed(char key);       // Check if a given key is being pressed
    char readKey();                 // Looks for a key that is being pressed; returns 255 is no key is pressed.
};

#endif