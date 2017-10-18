PROGRAM1 README

Author: Brian Liebe

1. To compile, use any of the following:
	make 
	make program1
	g++ program1.cpp -o program1 -std=c++11

2. Then you can run the program with:
	./program1 <file> <file> <output>


This program is very fast due to the memoization and the lack of repetition.

getFirstLine() - gets the first like of the input files
main() - the majority of the program,  it uses two array (one for the stored
	values, and one for the direction). Then depending on sequence length
	the program will print either the full array or the answer
