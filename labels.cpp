//
//  labels.cpp
//  ECS_040_Program_04
//
//  Created by Justin Weich on 2/7/16.
//  Copyright © 2016 Justin Weich. All rights reserved.
//

#include "labels.h"


fstream& operator>>(fstream& inf, Labels& labels)
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
			address += 4;
		} // if not directive, nor main:
		
		// if the current thing is acutally a label, set the address to address and
		// do stuff.
			labels.instruction[instructionCount].setAddress(address);
			labels.instruction[instructionCount++].setInfo(line);
		
	}  // while more in file
	inf.clear();
	inf.seekg(0, inf.beg);
	return inf;
}