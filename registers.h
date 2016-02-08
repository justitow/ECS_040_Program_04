#ifndef REGISTERS_H
#define	REGISTERS_H
// Author: Sean Davis

#include <iostream>

using namespace std;


class Registers 
{
  int regs[6];
public:
	typedef enum {eax, ebp, esp, eip, edx, flags} RegName;
	
	Registers();
  int* address(char *ptr, int memory[]);
  int get(RegName regName) const;
  void set(RegName regName, int value);
	friend ostream& operator<<(ostream& cout, Registers& registers);
}; // class Registers




#endif	// REGISTERS_H 

