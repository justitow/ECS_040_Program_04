//
//  labels.cpp
//  ECS_040_Program_04
//
//  Created by Justin Weich on 2/7/16.
//  Copyright © 2016 Justin Weich. All rights reserved.
//


#include <cstring>
#include "labels.h"

ifstream& operator>>(ifstream& inf, Labels& labels)
{
  
  char line[256], *ptr;
  int address = 100;
  labels.count = 0;

  while(inf.getline(line, 256))
  {
    for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters

    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces
    
    if(*ptr != '.' && !strstr(line, "main:"))
    {
      address += 4;
    } // if not directive, nor main:

    if ((*ptr == '.' && *(ptr + 1) == 'L') || *ptr == '_')
    {
      labels.instruction[labels.count].setAddress(address);

      if ((ptr = strchr(line, ':')))
      {
        *ptr = '\0';
      } // if there wasn't a colon

      labels.instruction[labels.count].setInfo(line);
      labels.count++;
    } //if there wasn't a label

  }  // while more in file

  inf.clear();
  inf.seekg(0, inf.beg);
  return inf;
} // operator>>()

int Labels::find(const char* line) const
{
  int index = 0;

  while (strcmp(instruction[index].getInfo(), line) != 0)
    index++;
  
  return instruction[index].getAddress();
  
} // find()
