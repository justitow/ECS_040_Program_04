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



int* Registers::address(char *operand, const Labels *labels, int memory[])
{
  static int value;
  char regNames[5][7] = {"eax", "ebp", "esp", "eip", "edx"};
  char *ptr, *first, *last, *firstE, *secondE, *lastParenth;
  int regNum, index, firstReg, secondReg, otherIndex;

  if(operand == NULL)
    return NULL;

  if(operand[0] == '$') // immediate mode
  {
    value = atoi(&operand[1]);
    return &value;
  } // if immediate mode


  if(operand[0] == '.' || operand[0] == '_')
  {
    value = labels->find(operand);
    return &value;
  } //otherwise no

  for(regNum = eax; regNum <= edx; regNum++)
    if(strstr(operand, regNames[regNum]))
      break;
  
  ptr = strchr(operand, '(');

  if(ptr) // some form of indirect addressing
  {
    first = strchr(operand, ',');
    last = strrchr(operand, ',');
    lastParenth = strchr(operand, ')');

    if ((first != last) && first != NULL)
    {
      firstE = strchr(operand, 'e');
      secondE = strrchr(operand, 'e');
      *first = '\0';

      for(firstReg = eax; firstReg <= edx; firstReg++)
        if(strstr(firstE, regNames[firstReg]))
          break;

      for(secondReg = eax; secondReg <= edx; secondReg++)
        if(strstr(secondE, regNames[secondReg]))
          break;

      *lastParenth = '\0';
      last++;
      
      otherIndex = atoi(last);
      *ptr = '\0';
      
      index = atoi(operand);
      return &memory[regs[firstReg] + regs[secondReg] * otherIndex + index];
    } // if

    *ptr = '\0';  // terminate operand string at first '('
    index = atoi(operand);  // will return 0 if no number there!
        
    return  &memory[regs[regNum] + index];
  } // if ptr

  else  // direct addressing
    return &(regs[regNum]);
} // address ()


int Registers::get(Registers::RegName regName) const
{
  if(regName < eax || regName > flags)
    return 0;
  
  return regs[regName];
}  // get()


void Registers::set(Registers::RegName regName, int value)
{
  if(regName >= eax && regName <= flags)
    regs[regName] = value;
} // set()


const void Registers::setFlags(const int i)
{
  if (i == 0)
  {
    regs[Registers::flags] = 0x40;
  } // not 0

  if (i < 0)
  {
    regs[Registers::flags] = 0x80;
  } // not negative
  
  if (i > 0)
  {
    regs[Registers::flags] = 0x00;
  } // not a number
  
} // Registers::setFlags()

const bool Registers::sf()
{

  if (regs[Registers::flags] == 0x80)
  {
    return true;
  } // if not zero
  
  return false;
} //sf()

const bool Registers::zf()
{
  
  if (regs[Registers::flags] == 0x40)
  {
    return true;
  } // if not negative
  
  return false;
} //zf()

ostream& operator<<(ostream& cout, Registers& registers)
{
  cout << left << " eip: " << right << setw(3)
  << registers.regs[Registers::eip] << " eax: " << setw(3)
  << registers.regs[Registers::eax] << " ebp: " << setw(3)
  << registers.regs[Registers::ebp] << " esp: " << setw(3)
  << registers.regs[Registers::esp] << " edx: " << setw(3)
  << registers.regs[Registers::edx] << " flags: " << setw(3)
  << registers.regs[Registers::flags] << endl;
  return cout;
} // << operator

const int& Registers::operator+=(const int &i)
{
  regs[Registers::esp] = regs[Registers::esp] + i;
  return regs[Registers::esp];
} //operator +=

