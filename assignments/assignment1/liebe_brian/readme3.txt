PROGRAM3 README

Author: Brian Liebe

1. To compile, use any of the following:
	make 
	make program3
	g++ program3.cpp -o program3 -std=c++11

2. Then you can run the program with:
	./program3 <file> <file> <output>

This runs nearly as fast as program1, and could potentially be faster.
If there was a perfect match between sequence x & y, then program 3 would 
be faster.

getFirstLine() - reads the first line of an input file
findMaxLCS() - recursively checks for matches. If there is a match, it adds
	one to the diagonal. Otherwise it uses the max of "up" and "left".
	Each value is set to negative infinity to start.
main() - sets the array to negative infinities and calls the recursive 
	function.
