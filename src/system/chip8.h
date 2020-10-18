#ifndef CHIP8_H
#define CHIP8_H
#define width 64
#define height 32

// Defines the CHIP-8 Hardware

// Single letter identifiers are CAPITALIZED
// All other identifiers are in camelCase
class Chip8 {
  public:
  union{
    unsigned char memory[0x1000];
    struct{
      // 16 Vx Registers, timers, and stack pointer (topmost level of stack)
      unsigned char V[16], delayTimer, soundTimer, stackPointer;
      // Index register (points to RAM address), program counter (pointer to currently executing instruction in memory), instruction stack, and current opcode (instruction)
      unsigned short I, programCounter, stack[16], opcode;
      // Character map
      unsigned char display[width*height/8];
    };
  };
  void initialize();
  void load();
  void emulatecycle();
};

#endif
