#ifndef DECODER_H
#define  DECODER_H
// Author: Sean Davis

#include "instruction.h"
#include "registers.h"
#include "labels.h"

class Decoder
{
  char opcode[20];
  int *operand1;
  int *operand2;
  void addl(Registers *registers);
  void andl(Registers *registers);
  void cmpl(Registers *registers) const;
  void incl(Registers *registers);
  void jg(Registers *registers);
  void jle(Registers *registers);
  void jmp(Registers *registers) const;
  void leal(Registers *registers) const;
  void leave(Registers *registers, int memory[1001]) const;
  void movl();
  void pushl(Registers *registers, int memory[1001]) const;
  void ret(Registers *registers, int memory[1001]) const;
  void subl(Registers *registers);
public:
  void execute(Registers *registers, int memory[1001]);
  void parse(Instruction *instruction, Registers *registers, Labels *labels,
             int memory[1001]);
}; // class Decoder;



#endif  // DECODER_H 

