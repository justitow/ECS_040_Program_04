#ifndef READER_H
#define  READER_H
// Author: Sean Davis

#include "instruction.h"
#include "registers.h"


#include <fstream>

using namespace std;
class Reader
{
private:
  Instruction lines[1000];
public:
  void fetch(Instruction *instruction, Registers *registers);
  friend ifstream& operator>>(ifstream& inf,  Reader &reader);
}; // Reader;


#endif  // READER_H 

