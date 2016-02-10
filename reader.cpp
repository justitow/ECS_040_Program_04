// Author: Sean Davis
#include <iostream>
#include <fstream>
#include <cstring>
#include "reader.h"
using namespace std;


void Reader::fetch(Instruction *instruction, Registers *registers)
{
  int pos;
  
  for(pos = 0; lines[pos].getAddress() != registers->get(Registers::eip);
			pos++);
  
  instruction->setInfo(lines[pos].getInfo());
  registers->set(Registers::eip, registers->get(Registers::eip) + 4);
} // fetch()

fstream &operator>>(fstream& inf, Reader& reader)
{
  char line[256], *ptr;
  int address = 100, instructionCount = 0;
  while(inf.getline(line, 256))
  {
    for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters
    
    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces
    
    if(*ptr != '.' && !strstr(line, "main:"))
    {
      reader.lines[instructionCount].setAddress(address);
      address += 4;
      reader.lines[instructionCount].setInfo(ptr);
			instructionCount++;
    } // if not directive, nor main:
  }  // while more in file
	inf.clear();
	inf.seekg(0, inf.beg);
	return inf;
}  // read()

