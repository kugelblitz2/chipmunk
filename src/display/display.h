#ifndef DISPLAY_H
#define DISPLAY_H
#include <curses.h>
#include <string>
#include <queue>
#include <utility>
#include "../config.h"
#include "../system/chip8.h"

// Handles display output for the CHIP-8 emulator
class display {
    public:
    int termX, termY;               // Keeps track of the size of the terminal
    int startY, startX;             // Keeps track of position of the Chip-8 window relative to the terminal
    WINDOW *emuScreen;              // ncurses window for the Chip-8's "video" output

    std::queue<std::pair <int,int> > updateQueue;   // Queue of positions <x, y> in the Chip-8 window to update
    chip8 *c8;                                       // Instance of the chip8 class pertaining to this instance of the display class

    display(chip8 *c8){
        this->c8 = c8;
    }

    // Functions pertaining to the CHIP-8 window
    WINDOW *initWindow();                   // Initializes the CHIP-8's window
    void updateWindow();                    // Re-renders the Chip-8 window (if necessary), and all new updates to the screen
    void displayMessage(std::string mesg);  // Display a message to the user (outside of the CHIP-8 window)
    void clearWindow(WINDOW *oldWindow);    // Removes the CHIP-8's window from the screen

    // Functions pertaining to the CHIP-8's video output
    void addToQueue(int x, int y);     // Adds position (x, y) to the update queue
    void updateScreen();                // Reads the update queue and updates the positions on screen
    void refreshScreen();               // Updates the entire screen regardless of the queue; clears the queue 
    
};

#endif