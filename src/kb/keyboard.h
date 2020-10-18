#ifndef KEYBOARD_H
#define KEYBOARD_H

// Virtual KB for the Chip-8
class keyboard(){
    public:
    // Represents the Chip-8's 16 key keyboard
    bool keypressed[4][4];
    unordered_map <short, pair<short, short> > keymap;

    // Keyboard functions
    void updatekey(int key);
    bool isitpressed(int key);
};