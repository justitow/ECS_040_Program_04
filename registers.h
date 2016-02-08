#ifndef REGISTERS_H
#define	REGISTERS_H
// Author: Sean Davis

typedef enum {eax, ebp, esp, eip, edx, flags} RegName;
 
class Registers 
{
  int regs[6];
public:
	Registers();
  int* address(char *ptr, int memory[]);
  int get(RegName regName) const;
  void print(const char *instruction) const;
  void set(RegName regName, int value);
}; // class Registers




#endif	// REGISTERS_H 

