#include <stdio.h>
#include "chip8.h"

// Emulates the CHIP-8 instruction set

// Single letter identifiers are CAPITALIZED
// All other identifiers are in camelCase
void Chip8::initialize(){
  //Resets program counter, opcode, index register, an stack pointer
  programCounter = 0x200;
  opcode = 0;
  I = 0;
  stackPointer = 0;

  //Load font into memory
  for(int i = 0; i < 80; i++) memory[i] = font[i];
  //Load program into memory
  for(int i = 0; i < bufferSize; i++) memory[i + 512] = buffer[i];
}
void Chip8::load(){}
void Chip8::emulatecycle(){
  // Fetch opcodes
  opcode = memory[programCounter] << 8 | memory[programCounter + 1];
  // Decode opcodes
  switch(opcode & 0xF000){
    // Execute Opcodes
    case 0x0000:  // 0xxx
      switch(opcode){
        case 0x00E0:  // Clear the display
          break;
        case 0x00EE:  // Return from subroutine
          if(stackPointer == 0) printf("Opcode 0x0EEE: Error: Cannot return: Instruction stack empty\n");
          else programCounter = stack[stackPointer]; stackPointer--;
          break;
      } break;
    case 0x1000:  // 1nnn: Sets program counter to nnn
      programCounter = opcode & 0x0FFF;
      break;
    case 0x2000:  // 2nnn: Executes subroutine at nnn
      stackPointer++;
      stack[stackpointer] = opcode & 0x0FFF;
      break;
    case 0x3000:  // 3xkk: if V[x] == kk, skip the next instruction
      if(V[(opcode & 0x0F00) / 0x100] == opcode & 0x00FF) programCounter+=2;
      break;
    case 0x4000:  // 4xkk: if V[x] != kk, skip the next instruction
      if(V[(opcode & 0x0F00) / 0x100] == opcode & 0x00FF) programCounter+=2;
      break;
    
  }

  // Update timers
}
