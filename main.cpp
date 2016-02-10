// Author: Sean Davis

#include "registers.h"
#include "decoder.h"
#include "reader.h"
#include "instruction.h"
#include "labels.h"

#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
  Reader reader;
  Decoder decoder;
  Registers registers;
  Instruction instruction;
	cout<<"hklhlh";
	Labels labels;
  int memory [1001];
	memory[1000] = 0;
	fstream inf;
	inf.open(argv[1]);
	
	inf >> reader;
	inf >> labels;

  while(registers.get(Registers::eip) != 0)
  {
    reader.fetch(&instruction, &registers);
    decoder.parse(&instruction, &registers, &labels, memory);
    decoder.execute(&registers, memory);
		cout << left << setw(20) << instruction.getInfo() << registers;
		
  } // while eip not zero
		
  return 0;
}  // main()

