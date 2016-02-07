#!  /bin/bash

testerDirectory="/home/ssdavis/40/p4/Testing"

if [ $# -ne 1 ]; then
  >&2 echo "usage DesignChecker.sh: $testerDirectory/DesignChecker.sh CPU.out_directory"
  exit
fi

if [[ $1 =~ Testing ]]; then # Use from this directory is not allowed
  >&2 echo "You may not use Testing as your own source directory!"
  exit
fi

cd $1

rm -f designResults.txt
designError=0
dos2unix *.cpp *.h &> /dev/null

grep "/\*" *.cpp *.h > temp
if [ -s temp ]; then
  cat temp >> designResults.txt
  echo 'Fatal design error: "\*" found.' >> designResults.txt
  (( ++designError ))
fi

openBracketCount=$( grep -v "//" *.h | grep "{" | wc -l )

if [ $openBracketCount -ne 7 ]; then
  echo 'Fatal design error: Implementation code found in header file.' >> designResults.txt
  (( ++designError ))
fi

if egrep "(struct |stdio|string\.h|stdlib\.h|malloc|free|print|fopen|read[^a-z])" *.h *.cpp >& /dev/null ; then
  echo 'Fatal design error: struct, stdio, string.h, stdlib.h, malloc, free,' >> designResults.txt
  echo 'print, fopen, or read found in file(s).' >> designResults.txt
  (( +designError ))
fi

grep -v "^ *//" *.cpp| awk '/void/ , /\)/' | grep ";" > temp

if [ -s temp ]; then
  echo 'Fatal design error: Prototype in *.cpp file.' >> designResults.txt
  (( ++designError ))
fi

# non-fatal design errors from here on


if ! grep "operator *>>" reader.h &> /dev/null ; then
  echo "operator>> not in reader.h" >> designResults.txt
fi

awk '/public/,/};/' decoder.h > public
awk '/class/,/public/' decoder.h > private


if ! grep "void *cmpl(" private  &> /dev/null || grep "cmpl" public  &> /dev/null ; then
  echo "cmpl( not private in decoder.h" >> designResults.txt
fi

if ! grep "void *incl(" private  &> /dev/null || grep "incl" public  &> /dev/null ; then
  echo "incl( not private in decoder.h" >> designResults.txt
fi

if ! grep "void *jg(" private  &> /dev/null || grep "jg" public  &> /dev/null ; then
  echo "jg( not private in decoder.h" >> designResults.txt
fi

if ! grep "void *jle(" private  &> /dev/null || grep "jle" public  &> /dev/null ; then
  echo "jle() not private in decoder.h" >> designResults.txt
fi

if ! grep "void *jmp(" private  &> /dev/null || grep "jmp" public  &> /dev/null ; then
  echo "jmp( not private in decoder.h" >> designResults.txt
fi

if ! grep "void *leal(" private  &> /dev/null || grep "leal" public  &> /dev/null ; then
  echo "ret() not private in decoder.h" >> designResults.txt
fi

if ! grep "void *call(" private  &> /dev/null || grep "call" public  &> /dev/null ; then
  echo "call() not private in decoder.h" >> designResults.txt
fi

if ! grep "void *sall(" private  &> /dev/null || grep "sall" public  &> /dev/null ; then
  echo "sall() not private in decoder.h" >> designResults.txt
fi

if ! awk '/parse/, /;/' public | grep "Labels"  &> /dev/null || grep "parse" private  &> /dev/null ; then
  echo "Labels passed in parse() not in public in decoder.h" >> designResults.txt
fi

if [[ ` grep -v "//" decoder.cpp | grep setFlags  | wc -l` -ne 6 ]]; then
  echo "setFlags not called proper number of times in decoder.cpp"  >> designResults.txt
fi

if [[ ` grep -v "//" decoder.cpp | grep += decoder.cpp | wc -l` -ne 3 ]]; then
  echo "+= not called proper number of times in decoder.cpp"  >> designResults.txt
fi


awk '/public/,/};/' registers.h > public
awk '/class/,/public/' registers.h > private

if ! grep "int regs\[6" private  &> /dev/null || grep "regs" public  &> /dev/null ; then
  echo "regs[6 not private in registers.h" >> designResults.txt
fi

if ! grep "address(.*Labels.*)" public  &> /dev/null ; then
  echo "Labels passed in address() not found in public in registers.h" >> designResults.txt
fi

if ! grep "typedef .*enum .*edx," registers.h  &> /dev/null ; then
  echo "edx enum not found in registers.h" >> designResults.txt
fi

if ! grep "typedef.*enum.*flags" registers.h  &> /dev/null ; then
  echo "flags enum not found in registers.h" >> designResults.txt
fi

if ! grep "operator *<<" registers.h  &> /dev/null ; then
  echo "operator<< not found in registers.h" >> designResults.txt
fi

if ! grep "operator *+=" registers.h  &> /dev/null ; then
  echo "operator+= not found in registers.h" >> designResults.txt
fi

echo $designError  # Only standard out

