PROGRAM2 README

AUTHOR: Brian Liebe

TO COMPILE:

	make
-or-
	g++ BestFirstSearch.cpp -o BestFirstSearch -std=c++11

TO RUN:

	./BestFirstSearch <input> <output>

OTHER DETAILS:

	I'm going off the assumption that the provided solution.txt is incorrect in the sense that the
	first line should not be "40,90,2" and should instead be "4,90,2" like is described in the 
	project2 instructions file on MyCourses.

EXPLANATION OF METHODS:

	struct node : stores price/profit, weight, level, bound, and the parents of each node

	bool initialSortFunction : sorts the items into ascending order based on profit/weight

	bool secondarySortFunction : sorts the nodes based on the bounds into ascending order

	float findBound : calulates the bound based on capacity, remaining items, price, and weight

	main : the majority of the program, including the algorithm
