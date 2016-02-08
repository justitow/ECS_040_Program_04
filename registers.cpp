// Author: Sean Davis
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "registers.h"
using namespace std;


Registers::Registers()
{
	regs[esp] = 1000;
	regs[ebp] = 996;
	regs[eip] = 100;
	regs[eax] = 0;
	regs[edx] = 0;
	regs[flags] = 0xC0;
}  // initialize()



int* Registers::address(char *operand, int memory[])
{
  static int value;
  char regNames[4][7] = {"eax", "ebp", "esp", "eip"};
  char *ptr;
  int regNum, index;

  if(operand == NULL)
    return NULL;

  if(operand[0] == '$') // immediate mode
  {
    value = atoi(&operand[1]);
    return &value;
  } // if immediate mode

  for(regNum = eax; regNum <= eip; regNum++)
    if(strstr(operand, regNames[regNum]))
      break;

  ptr = strchr(operand, '(');

  if(ptr) // some form of indirect addressing
  {
    *ptr = '\0';  // terminate operand string at first '('
    index = atoi(operand);  // will return 0 if no number there!
    return  &memory[regs[regNum] + index];
  } // if ptr
  else  // direct addressing
    return &(regs[regNum]);
} // address ()


int Registers::get(Registers::RegName regName) const
{
  if(regName < eax || regName > eip)
    return 0;
  
  return regs[regName];
}  // get()


void Registers::set(Registers::RegName regName, int value)
{
  if(regName >= eax && regName <= eip)
    regs[regName] = value;
} // set()


ostream& operator<<(ostream& cout, Registers& registers)
{
	cout << left << " eip: " << right << setw(3)
	<< registers.regs[Registers::eip] << " eax: " << setw(3)
	<< registers.regs[Registers::eax] << " ebp: " << setw(3)
	<< registers.regs[Registers::ebp] << " esp: "<< setw(3)
	<< registers.regs[Registers::esp] << " edx: " << setw(3)
	<< registers.regs[Registers::edx] << " flags: " << setw(3)
	<< registers.regs[Registers::flags] << endl;
	return cout;
} // << operator

int& Registers::operator+=(int &i)
{
	regs[Registers::esp] += i;
	return regs[Registers::esp];
} //operator +=

