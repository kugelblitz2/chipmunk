#ifndef IO_H
#define IO_H
#include <curses.h>
#include <string>
#include "../system/chip8.h"

// Handles display output for the CHIP-8 emulator
class display {
    public:
    // Keeps track of the size of the terminal
    int termX, termY;
    // Keeps track of position of the Chip-8 window relative to the terminal
    int startY, startX;
    // ncurses window for the Chip-8's "video" output
    WINDOW *emuScreen;

    WINDOW *initWindow();                   // Initializes the CHIP-8's window
    void updateWindow();                    // Re-renders the Chip-8 window (if necessary), and all new updates to the screen
    void displayMessage(std::string mesg);  // Display a message to the user (outside of the CHIP-8 window)
    void clearWindow(WINDOW *oldWindow);    // Removes the CHIP-8's window from the screen
};

// Virtual KB for the Chip-8
class keyboard {
    public:
    // The states of each key for the Chip-8's 16 key keyboard
    bool keypressed[16];
    // Maps real keyboard keys to Chip-8 keys
    //std::unordered_map <short, short> keymap;

    // Keyboard functions
    void updateKey(int key);        // Updates the status of a given key (set a key to pressed or unpressed)
    bool isPressed(int key);        // Check if a given key is being pressed
};

#endif