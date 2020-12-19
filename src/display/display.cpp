#include "display.h"

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
    // Checks if the terminal window is big enough for a Chip-8 window
    if(LINES < height + 3 || COLS < width + 2){
        displayMessage("Error: Terminal window too small for emulator; please resize");
    }
    // Checks if the Chip-8 window needs to be re-rendered
    else if(LINES != display::termY && COLS != display::termX){
        clearWindow(emuScreen);

        termY = LINES; termX = COLS;
        emuScreen = initWindow();
    }
}

void display::displayMessage(std::string mesg){
    // Display a given message on the screen.
    mvprintw(0, 0, "%s", mesg);
}

void display::clearWindow(WINDOW *oldWindow){
    // Clears the content in the window before deleting it
    wclear(oldWindow);
    wrefresh(oldWindow);
    delwin(oldWindow);
}

void display::addToQueue(int x, int y){
    updateQueue.push(std::pair<int,int> (x, y));
}

void display::updateScreen(){
    // Updates characters on the screen until the queue is empty
    while(!updateQueue.empty()){
        int y = updateQueue.front().second;         // X position of the character to be updated - CURRENTLY 0 INDEXED; Verify when finishing the instruction set
        int x = updateQueue.front().first;          // Y position of the character to be updated - CURRENTLY 0 INDEXED; Verify when finishing the instruction set
        char ch = c8.displayMap[x][y];              // Checks the character map and from memory and determines the character to be written

        mvwaddch(emuScreen, y+1, x+1, ch);          // Updates the character at the specified position
        updateQueue.pop();                          // Removes the update query from the queue
    }
}

void display::refreshScreen(){
    // Updates every character on the screen
    for(int i = 0; i < 64; i++){
        for(int j = 0; j < 32; j++){
            char ch = c8.displayMap[i][j];          // Checks the character map and from memory and determines the character to be written
            mvwaddch(emuScreen, i+1, j+1, ch);      // Updates the character at the specified position
        }
    }
    // Replaces updateQueue with an empty queue
    std::queue<std::pair<int,int>> q;
    std::swap(updateQueue, q);
}