#include "io.h"

WINDOW *display::initWindow(){
    // Create new window
    WINDOW *newWindow;

    // Calculates the position of the window
    startY = (termY - (height+2)) / 2;
    startX = (termX - (width+2)) / 2;

    // Creates the window
    newWindow = newwin(height+2, width+2, startY, startX);
    box(newWindow, 0, 0);          // Creates the outline around the window
    wrefresh(newWindow);

    // Return said window
    return newWindow;
}

void display::updateWindow(){
    // Checks if the Chip-8 window needs to be re-rendered
    if(LINES != display::termY && COLS != display::termX){
        clearWindow(emuScreen);

        termY = LINES; termX = COLS;
        emuScreen = initWindow();
    }
}

void display::displayMessage(){
    
}

void display::clearWindow(WINDOW *oldWindow){

    // Clears the content in the window before deleting it
    wclear(oldWindow);
    wrefresh(oldWindow);
    delwin(oldWindow);
}