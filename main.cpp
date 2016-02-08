// Author: Sean Davis

#include "registers.h"
#include "decoder.h"
#include "reader.h"
#include "instruction.h"
#include "labels.h"

int main(int argc, char* argv[])
{
  Reader reader;
  Decoder decoder;
  Registers registers;
  Instruction instruction;
	Labels labels;
  int memory [1001];
  registers.initialize(memory);
	fstream inf(argv[1]);
	inf >> reader;
	inf >> labels;

  while(registers.get(eip) != 0)
  {
    reader.fetch(&instruction, &registers);
    decoder.parse(&instruction, &registers, memory);
    decoder.execute(&registers, memory);
    registers.print(instruction.getInfo());
  } // while eip not zero
  
  return 0;
}  // main()

