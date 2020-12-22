#ifndef CHIP8_H
#define CHIP8_H
#include <stdlib.h>
#include <time.h>
#include "../config.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"

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

  display disp;
  keyboard kb;
  bool pauseInstructions;

  chip8(int programSize, int *font, int *program){
    disp = new display(this);
    kb = new keyboard();
    pauseInstructions = false;

    srand(time(NULL));                                  // Seed the RNG

    for(int i = 0; i < 80; i++) memory[i] = font[i];    // Load font into memory
    loadProgram(programSize, program);                  // Load program into memory
  }

  void loadProgram(int programSize, int *program);
  void processInstruction();
  void updateTimer();
};

#endif
