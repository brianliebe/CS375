PROGRAM2 README

Author: Brian Liebe

1. To compile, use any of the following:
	make 
	make program2
	g++ program2.cpp -o program2 -std=c++11

2. Then you can run the program with:
	./program2 <file> <file> <output>


The algorithm being executed here is pretty slow, in fact it's significantly
slower than program1 or program3. It's recursive, and as such it will call the
same problem mulitple times (since there is no memoization).

getFirstLine() - is used to get the first line of an input file (the sequence)
findMaxLCS() - is the main recursive call, which determines the LCS
main() - is the non-recursive time
