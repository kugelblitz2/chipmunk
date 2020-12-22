#include <stdlib.h>
#include "chip8.h"

// Load program
void chip8::loadProgram(int programSize, int *program){
  // Resets program counter, opcode, index register, an stack pointer
  programCounter = 0x200;
  I = 0;
  stackPointer = 0;
  // Copies program into memory
  for(int i = 0; i < programSize; i++) memory[i + 0x200] = program[i];
}

// Updates timers
void chip8::updateTimer(){
  if(delayTimer != 0) delayTimer--;
  if(soundTimer != 0) soundTimer--;
  return;
}


// Emulates the CHIP-8 instruction set
void chip8::processInstruction(){
  // Fetch opcodes
  unsigned short opcode = memory[programCounter] << 8 | memory[programCounter + 1];
  // Decode opcodes (instruction set)
  switch(opcode & 0xF000){
    // Execute Opcodes
    case 0x0000:  // 0xxx
      switch(opcode){
        case 0x00E0:  // Clear the display
          memset(displayMap, 0, height*width);
          disp.refreshScreen();
          break;
        case 0x00EE:  // Return from subroutine
          stackPointer--;
          programCounter = stack[stackPointer];
          break;
      } break;
    case 0x1000:  // 1nnn: Sets program counter to nnn
      programCounter = opcode & 0x0FFF;
      break;
    case 0x2000:  // 2nnn: Executes subroutine at nnn
      stackPointer++;
      stack[stackPointer] = programCounter+2;
      programCounter = opcode & 0x0FFF;
      break;
    case 0x3000:  // 3xkk: if V[x] == kk, skip the next instruction
      if(V[(opcode & 0x0F00) / 0x100] == opcode & 0x00FF) programCounter+=4;
      else programCounter+=2;
      break;
    case 0x4000:  // 4xkk: if V[x] != kk, skip the next instruction
      if(V[(opcode & 0x0F00) / 0x100] == opcode & 0x00FF) programCounter+=4;
      else programCounter+=2;
      break;
    case 0x5000:  // 5xy0: if V[x] == V[y], skip the next instruction
      if(V[(opcode & 0x0F00) / 0x100] == V[(opcode & 0x00F0) / 0x10]) programCounter+=4;
      else programCounter+=2;
      break;
    case 0x6000:  // 6xkk: sets V[x] to kk
      V[(opcode & 0x0F00) / 0x100] = opcode & 0x00FF;
      programCounter+=2;
      break;
    case 0x7000:  // 7xkk: V[x] += kk
      V[(opcode & 0x0F00) / 0x100] += opcode & 0x00FF;
      programCounter+=2;
      break;
    case 0x8000:  // 0xxx
     switch(opcode & 0x000F){
        case 0x0000:  // 8xy0: V[x] = V[y]
          V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x00F0) / 0x0010];
          programCounter+=2;
          break;
        case 0x0001:  // 8xy1: V[x] = V[x] OR V[y]
          V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] | V[(opcode & 0x00F0) / 0x0010];
          programCounter+=2;
          break;
        case 0x0002:  // 8xy2: V[x] = V[x] AND V[y]
          V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] & V[(opcode & 0x00F0) / 0x0010];
          programCounter+=2;
          break;
        case 0x0003:  // 8xy3: V[x] = V[x] XOR V[y]
          V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] ^ V[(opcode & 0x00F0) / 0x0010];
          programCounter+=2;
          break;
        case 0x0004:  // 8xy4: V[x] = V[x] + V[y], V[F] = integer overflow
          int i = V[(opcode & 0x0F00) / 0x0100] + V[(opcode & 0x00F0) / 0x0010];
          if(i > 255) V[0xF] = 1;
          else V[0xF] = 0;
          V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] + V[(opcode & 0x00F0) / 0x0010];
          programCounter+=2;
          break;
        case 0x0005:  //8xy4: V[x] = V[x] + V[y], V[F] = not borrowing
          if(V[(opcode & 0x0F00) / 0x0100] < V[(opcode & 0x00F0) / 0x0010]){
            V[0xF] = 0; // Borrow
            V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x00F0) / 0x0010] - V[(opcode & 0x0F00) / 0x0100];
          }
          else{
            V[0xF] = 1; // Don't borrow
            V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] - V[(opcode & 0x00F0) / 0x0010];
          }
          programCounter+=2;
          break;
        case 0x0006:  //8xy6: V[F] = least significant bit of V[x], V[x] /= 2
          V[(opcode & 0x0F00) / 0x0100] & 0x000F == 1 ? V[0xF] = 1 : V[0xF] == 0;
          V[(opcode & 0x0F00) / 0x0100] /= 2;
          programCounter+=2;
          break;
        case 0x0007:  //8xy7:
          if(V[(opcode & 0x00F0) / 0x0010] < V[(opcode & 0x0F00) / 0x0100]){
            V[0xF] = 0; // Borrow
            V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x0F00) / 0x0100] - V[(opcode & 0x00F0) / 0x0010];
          }
          else{
            V[0xF] = 1; // Don't borrow
            V[(opcode & 0x0F00) / 0x0100] = V[(opcode & 0x00F0) / 0x0010] - V[(opcode & 0x0F00) / 0x0100];
          }
          programCounter+=2;
          break;
        case 0x000E:  // 8xyE: V[F] = least significant bit of V[x], V[x] *= 2
          V[(opcode & 0x0F00) / 0x0100] & 0x000F == 1 ? V[0xF] = 1 : V[0x000F] == 0;
          V[(opcode & 0x0F00) / 0x0100] *= 2;
          programCounter+=2;
          break;
     } break;
    case 0x9000:  // 9xy0: if V[x] != V[y], skip the next instruction
      if(V[(opcode & 0x0F00) / 0x0100] != V[(opcode & 0x00F0) / 0x0010]) programCounter+=4;
      programCounter+=2;
      break;
    case 0xA000:  // Annn: set I = nnn
      I = opcode & 0x0FFF;
      programCounter+=2;
      break;
    case 0xB000:  // Bnnn: set programCounter = nnn + V[0]
      programCounter = (opcode & 0x0FFF) + V[0];
      programCounter+=2;
      break;
    case 0xC000:  // Cxkk: V[x] = rand % 255 & kk
      V[opcode & 0x0F00 / 0x0100] = (rand() % 255) & (opcode & 0x00FF);
      programCounter+=2;
      break;
    case 0xD000:  // Dxyn: XORs a n-byte starting at I sprite onto the screen at x, y. V[F] = 1 if any pixels are erased
      // DO SMTH
      unsigned char bytes = opcode % 0x000F;
      unsigned char x = opcode % 0x0F00 / 0x0100;
      unsigned char y = opcode % 0x00F0 / 0x0010;

      V[0x000F] = 0;
      for(int line = 0; line < bytes; line++){
        unsigned char thisline = memory[I+line];
        for(int col = 0; col < 8; col++){
          if(displayMap[V[x]+col][V[y]+line] == (thisline >> col)) V[0x000F] = 1;
          displayMap[V[x]+col][V[y]+line] = displayMap[V[x]+col][V[y]+line] ^ (thisline >> col);
          disp.addToQueue(col, line);
        }
      }
      disp.updateScreen();
      programCounter+=2;
      break; 
    case 0xE000:  // Exxx
      switch(opcode & 0x00FF){
        case 0x009E:  // Ex9E: Skip the next instruction if the key indicated by V[x] is pressed
          if(kb.isPressed(V[(opcode & 0x0F00) / 0x0100])) programCounter+=4;
          else programCounter+=2;
          break;
        case 0x00A1: // ExA1: Skip the next instruction if the key indicated by V[x] is not pressed
          if(!kb.isPressed(V[(opcode & 0x0F00) / 0x0100])) programCounter+=4;
          else programCounter+=2;
          break;
      } break;
    case 0xF000:  // Fxxx
      switch(opcode & 0x00FF){
        case 0x0007:  // Fx07: V[x] = delayTimer
          V[(opcode & 0x0F00) / 0x0100] = delayTimer;
          programCounter+=2;
          break;
        case 0x000A:  // Fx0A: Waits for a keypress, pausing all other execution of instructions, and stores the key value in V[x]
          char key = kb.readKey();
          if(key != 255) V[(opcode & 0x0F00) / 0x0100] = key; programCounter+=2;
          break;
        case 0x0015:  // Fx15: Sets the delayTimer to V[x]
          delayTimer = V[(opcode & 0x0F00) / 0x0100];
          programCounter+=2;
          break;
        case 0x0018:  // Fx18: Sets soundTimer to V[x]
          soundTimer = V[(opcode & 0x0F00) / 0x0100];
          programCounter+=2;
          break;
        case 0x001E:  // Fx1E: I = I + V[x]
          I += V[(opcode & 0x0F00) / 0x0100];
          programCounter+=2;
          break;
        case 0x0029:  // Fx29: Sets I to the memory address of the character cooresponding to V[x]
          I = V[(opcode & 0x0F00) / 0x0100] * 5;
          programCounter+=2;
          break;
        case 0x0033:  // Fx33: IN DECIMAL, NOT HEX, store the hundreds value of V[x] at I, the tens value at I+1, and the ones value at I+2
          char hun, ten, one;
          hun = V[(opcode & 0x0F00) / 0x0100] / 100;
          ten = V[(opcode & 0x0F00) / 0x0100] % 100 / 10;
          one = V[(opcode & 0x0F00) / 0x0100] % 10;
          programCounter+=2;
          break;
        case 0x0055:  // Fx55: Store V[0] thru V[x] inclusive to memory, starting at I
          for(int i = 0; i <= (opcode & 0x0F00) / 0x0100; i++) memory[I+i] = V[i];
          programCounter+=2;
          break;
        case 0x0065:  // Fx65: Read x+1 bytes from memory to the V registers (V[0] to V[x]), starting from I
          for(int i = 0; i <= (opcode & 0x0F00) / 0x0100; i++) V[i] = memory[I+i];
          programCounter+=2;
          break;
      } break;
  }
}
