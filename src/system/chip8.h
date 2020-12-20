#ifndef CHIP8_H
#define CHIP8_H
#include "../config.h"
#include "../display/display.h"

// Defines the CHIP-8 Hardware

// Single letter identifiers are CAPITALIZED
// All other identifiers are in camelCase
class chip8 {
  public:
  union{    // CHIP-8 memory structure
    unsigned char memory[0x1000];
    struct{
      // CHIP-8 font sprites, starting at I = 0x0000
      unsigned char charMap[16*5];
      // 16 Vx Registers, timers, and stack pointer (topmost level of stack)
      unsigned char V[16], delayTimer, soundTimer, stackPointer;
      // Index register (points to RAM address), program counter (pointer to currently executing instruction in memory), instruction stack, and current opcode (instruction)
      unsigned short I, programCounter, stack[16], opcode;
      // Character map (what's being displayed on the CHIP-8 window)
      unsigned char displayMap[width][height];
      
    };
  };

  display disp = new display(this);
  keyboard kb = new keyboard();
  bool pause = false;

  void initialize(int bufferSize, int *font, int *buffer);
  void load();
  void emulatecycle();
};

#endif
