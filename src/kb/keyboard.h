#ifndef KEYBOARD_H
#define KEYBOARD_H

// Virtual KB for the Chip-8
class keyboard(){
    public:
    // The states of each key for the Chip-8's 16 key keyboard
    bool keypressed[16];
    // Maps real keyboard keys to Chip-8 keys
    unordered_map <short, short> keymap;

    // Keyboard functions
    void updatekey(int key);        // Updates the status of a given key (set a key to pressed or unpressed)
    bool ispressed(int key);        // Check if a given key is being pressed
};