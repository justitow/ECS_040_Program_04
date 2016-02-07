#ifndef REGISTERS_H
#define	REGISTERS_H
// Author: Sean Davis

typedef enum {eax, ebp, esp, eip} RegName;
 
class Registers 
{
  int regs[4];
public:
  int* address(char *ptr, int memory[]);
  int get(RegName regName) const;
  void initialize(int memory[1001]);
  void print(const char *instruction) const;
  void set(RegName regName, int value);
}; // class Registers




#endif	// REGISTERS_H 

