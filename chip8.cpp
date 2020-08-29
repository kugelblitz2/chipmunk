#include <stdio.h>
#include "chip8.h"

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
    case 0x1000:  // 1xxx: Sets program counter to xxx

    case 0xA000:  // Axxx: Sets I to the adress xxx
      I = opcode & 0x0FFF;
      pc += 2; break;
  }

  // Update timers
}
