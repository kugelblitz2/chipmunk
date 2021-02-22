#include <iostream>
#include <string>
#include "system/chip8.h"
#include "fontset.h"
#include "config.h"

int main(int argc, char* argv){

    // Handles command line arguments
    if(argc == 1 && &argv[1] == "help"){
        std::cout << "Usage: " << argv[0] << " [Scale] [Tick] [ROM]\n";
        std::cout << "Scale: The default CHIP-8 display is only 64*32, this integer describes by what factor the CHIP-8 screen should be scaled up by\n";
        std::cout << "Tick: The length of a processor tick in milliseconds\n";
        std::cout << "ROM: The path to the CHIP-8 ROM file to load" << std::endl;
        return 0;
    }
    else if(argc != 4){
        std::cerr << "Usage: " << argv[0] << " [Scale] [Display] [ROM]; Type \"" << argv[0] << " help\" for help" << std::endl;
        return 1;
    }

    scale = std::stoi(&argv[1]);
    int tickTime = std::stoi(&argv[2]);
    char* romPath = &argv[3];

    chip8 chip8(romPath, fontSet);

    bool quit = false;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();

    while (!quit){
        auto currentTime = std::chrono::high_resolution_clock::now();
        double deltaTime =  std::chrono::duration<double, std::chrono::milliseconds>(currentTime - lastCycleTime).count();

        if(deltaTime >= tickTime){
            lastCycleTime = currentTime;
            quit = chip8.processorCycle();
        }
    }

    return 0;
}