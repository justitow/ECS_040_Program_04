
//
//  labels.hpp
//  ECS_040_Program_04
//
//  Created by Justin Weich on 2/7/16.
//  Copyright © 2016 Justin Weich. All rights reserved.
//

#ifndef labels_h
#define labels_h

#include <iostream>
#include <fstream>
#include "instruction.h"

using namespace std;

class Labels
{
private:
	int count;
	Instruction instruction[100];
public:
	int find(const char* line) const;
	friend fstream& operator>>(fstream& inf, Labels& labels);
	
};

#endif /* labels_h */
