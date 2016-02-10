// Author: Sean Davis
#include <cstring>
#include <iostream>
#include "decoder.h"
#include "instruction.h"
#include "registers.h"
using namespace std;

void Decoder::addl(Registers* registers)
{
  *operand2 = *operand1 + *operand2;
  registers->setFlags(*operand2);
}  // addl()

void Decoder::andl(Registers* registers)
{
  *operand2 = *operand1 & *operand2;
  registers->setFlags(*operand2);
}  // andl()

void Decoder::cmpl(Registers* registers) const
{
  registers->setFlags(*operand2 - *operand1);
} //cmpl

void Decoder::execute(Registers *registers, int memory[1001])
{
  const char *opcodes[] = { "addl", "andl", "leave", "movl", "pushl", "ret",
    "subl", "cmpl", "incl", "jg", "jle", "jmp", "leal"};
  enum OpcodeNum {ADDL, ANDL, LEAVE, MOVL, PUSHL, RET, SUBL, CMPL, INCL, JG,
    JLE, JMP, LEAL};
  int opcodeNum;

  for(opcodeNum = ADDL;
    strcmp(opcode, opcodes[opcodeNum]) != 0 || opcodeNum > LEAL;
    ++opcodeNum);

  switch (opcodeNum)
  {
    case ADDL: addl(registers); break;
    case ANDL: andl(registers); break;
    case LEAVE: leave(registers, memory); break;
    case MOVL: movl(); break;
    case PUSHL: pushl(registers, memory); break;
    case RET: ret(registers, memory); break;
    case SUBL: subl(registers); break;
    case CMPL: cmpl(registers); break;
    case INCL: incl(registers); break;
    case JG: jg(registers); break;
    case JLE: jle(registers); break;
    case JMP: jmp(registers); break;
    case LEAL: leal(); break;
    default: cout << "Invalid opcode!\n";
  } // switch on oncodeNum

}  // execute()

void Decoder::incl(Registers *registers)
{
  *operand1 += 1;
  registers->setFlags(*operand1);
} // incl()

void Decoder::jg(Registers *registers)
{
  if (!registers->sf() && !registers->zf())
  {
    registers->set(Registers::eip, *operand1);
  } // if()
} //jg()

void Decoder::jle(Registers *registers)
{
  if (registers->sf() || registers->zf())
  {
    registers->set(Registers::eip, *operand1);
  }// if not sf flag or zf flag
} // jle()

void Decoder::jmp(Registers *registers) const
{
  registers->set(Registers::eip, *operand1);
} //jmp()

void Decoder::leal()
{

} // leal

void Decoder::leave(Registers *registers, int memory[1001]) const
{
  registers->set(Registers::esp, registers->get(Registers::ebp));
  registers->set(Registers::ebp, memory[registers->get(Registers::esp)]);
  *registers += 4;
}  // leave()


void Decoder::movl()
{
  *operand2 = *operand1;
}  // movl()


void Decoder::parse(Instruction *instruction, Registers *registers,
                    Labels *labels, int memory[1001])
{
  char *ptr, info[1000];

  strcpy(info, instruction->getInfo());
  strcpy(opcode, strtok(info, " "));
  ptr = strtok(NULL, " ");

  if(ptr)
  {
    operand1 = registers->address(ptr, labels, memory);
    ptr = strtok(NULL, " ");

    if(ptr)
      operand2 = registers->address(ptr, labels, memory);
  } // if there is at least one operand
}  // parse()





void Decoder::pushl(Registers *registers, int memory[1001]) const
{
  *registers += -4;
  memory[registers->get(Registers::esp)] = *operand1;
}  // pushl()


void Decoder::ret(Registers *registers, int memory[1001]) const
{
  registers->set(Registers::eip, memory[registers->get(Registers::esp)]);
  *registers += 4;
}  // ret()


void Decoder::subl(Registers* registers)
{
  *operand2 = *operand2 - *operand1;
  registers->setFlags(*operand2);
}  // subl()
