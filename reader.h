#ifndef READER_H
#define	READER_H
// Author: Sean Davis

#include "instruction.h"
#include "registers.h"

class Reader
{
  Instruction lines[1000];
public:
  void fetch(Instruction *instruction, Registers *registers);
  void read(Registers *registers, const char *filename);
}; // Reader;


#endif	// READER_H 

