#ifndef CHIP8_H
#define CHIP8_H
#include <chrono>
#include "../config.h"

// Defines the CHIP-8 Hardware

// Single letter identifiers are CAPITALIZED
// All other identifiers are in camelCase
class chip8 {
  public:
  unsigned char memory[0x1000];               // CHIP-8 memory structure

  // Memory pointers
  unsigned short I;                           // Index register (points to RAM address)
  unsigned short programCounter;              // Program counter (pointer to currently executing instruction in memory)
  
  // Registers and stacks
  unsigned char V[16];                        // 16 Vx registers
  unsigned short stack[16];                   // Instruction stack
  unsigned char stackPointer;                 // points to the top element of the stack

  // Timers
  unsigned char delayTimer, soundTimer;

  // Display map
  unsigned char displayMap[width][height];    // Character map (what's being displayed on the CHIP-8 window)

  bool pauseInstructions;

  chip8(char* romPath, char *font){
    pauseInstructions = false;

    srand(std::chrono::system_clock.now().time_since_epoch().count());                        // Seed the RNG

    for(int i = 0; i < 0x50; i++) memory[i] = font[i];  // Load font into memory
    loadProgram(romPath);                     // Load program into memory
  }

  void loadProgram(char* romPath);
  bool processorCycle();
  void updateTimer();
};

#endif
