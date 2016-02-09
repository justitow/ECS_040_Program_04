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
  void addl(Registers *registers);
  void andl(Registers *registers);
  void leave(Registers *registers, int memory[1001]) const;
  void movl();
  void pushl(Registers *registers, int memory[1001]) const;
  void ret(Registers *registers, int memory[1001]) const;
  void subl(Registers *registers);
public:
  void execute(Registers *registers, int memory[1001]);
  void parse(Instruction *instruction, Registers *registers, int memory[1001]);
}; // class Decoder;



#endif	// DECODER_H 

