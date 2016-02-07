#ifndef DECODER_H
#define	DECODER_H
// Author: Sean Davis

#include "instruction.h"
#include "registers.h"

class Decoder
{
  char opcode[20];
  int *operand1;
  int *operand2;
  void addl();
  void andl();
  void leave(Registers *registers, int memory[1001]) const;
  void movl();
  void pushl(Registers *registers, int memory[1001]) const;
  void ret(Registers *registers, int memory[1001]) const;
  void subl();
public:
  void execute(Registers *registers, int memory[1001]);
  void parse(Instruction *instruction, Registers *registers, int memory[1001]);
}; // class Decoder;



#endif	// DECODER_H 

