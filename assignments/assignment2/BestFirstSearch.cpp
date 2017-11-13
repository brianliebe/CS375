#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
struct used for saving all necessary information about each vertice, including
price, weight, level, bound, and parent nodes (which items it uses).
*/
struct node
{
	int price; 				// the total price so far
	int weight;				// the total weight so far
	int level;				// the level that the node is at (used with parents)
	float bound;			// the calculated bound for the node
	vector<int> parents;	// the items that the node relies on
	node() // the default constructor
	{
		price = 0;
		weight = 0;
		level = 0;
		bound = 0.0;
	}
	node (int a, int b, int c, float d) // set each value (except parents)
	{
		weight = a;
		price = b;
		level = c;
		bound = d;
	}
	void printData() // used for debugging
	{
		cout << "P: " << price << " W: " << weight << " L: " << level << " B: " << bound << endl;
		cout << "	parents: ";
		for (int m: parents) cout << m << " ";
		cout << endl;
	}
};

/*
Sorts the initial data read in from the file into non-descending order based on price/weight.
*/
bool initialSortFunction (pair<int, int> i, pair<int, int> j)
{
	float a = (float)i.second / i.first; // price/weight of item1
	float b = (float)j.second / j.first; // price/weight of item2
	return (a > b);
}

/*
Sorts the nodes based on their bounds, used with a priority queue.
*/
bool secondarySortFunction(node i, node j)
{
	return (i.bound < j.bound);
}

/*
Calculates the bound of the node based on capacity, current price & weight, and the remaining items
*/
float findBound (int price, int weight, int capacity, vector<pair<int, int>> remaining)
{
	capacity -= weight; // remove initial weight
	float bound = price; // bound must include current price
	for (pair<int, int> p: remaining) // move through remaining items
	{
		if (capacity > 0)
		{
			if (p.first <= capacity) // if the item fits well, then add it normally
			{
				bound += p.second;
				capacity -= p.first;
			}
			else // if the item doesn't fully fit, add part of it
			{
				bound += (float)capacity * ((float)p.second / p.first);
				capacity = 0;
			}
		}
	}
	return bound;
}

/*
The majority of the program. Reads the file, performs algorithm, and prints to output file.
*/
int main(int argc, char ** argv)
{
	ifstream input(argv[1]); 	// the input stream
	ofstream output(argv[2]); 	// the output stream

	int a,b; // the two values read from the file
	char ch; // the char between the two values (always ",")
	bool firstline(true); // distinguishes between first line (constraints) and the items.

	int capacity = 0; 				// total capacity
	int totalItems = 0;				// total items for the problem
	vector<pair<int, int>> items;	// vector to store <weight, price> pairs

	while (input >> a >> ch >> b) // move through the input file
	{
		if (firstline)
		{
			totalItems = a;
			capacity = b;
			firstline = false;
		}
		else // for items, just add it to the vector
		{
			items.push_back(pair<int, int>(a,b));
		}
	}
	input.close(); // close stream

	sort(items.begin(), items.end(), initialSortFunction); // sort the items based on price/weight.
	vector<node> queue; // create a priority queue for storing our nodes

	int visitedTotal = 0; 	// the total nodes we visit
	int visitedLeaf = 0;	// the total leaf nodes we visit
	node currentBestNode;	// the best node we have so far

	node root(0, 0, -1, findBound(0, 0, capacity, items)); // the root node, which has 0 items
	queue.push_back(root); // enqueue the root

	while(queue.size() > 0)
	{
		sort(queue.begin(), queue.end(), secondarySortFunction); // sort the queue to make it a priority queue
		node current = queue.back(); // dequeue the top priority node
		queue.pop_back();
		visitedTotal++; // we've visiting this node, so increase visitedTotal

		if (current.bound >= currentBestNode.price && current.weight < capacity) // fits our constraints
		{
			if (current.price > currentBestNode.price)
			{
				currentBestNode = current; // if this node is better, we use it instead
			}
			if (current.level + 1 < totalItems) // make sure we didn't run out of items
			{
				vector<pair<int, int>> remaining; // we need the remaining items to calculate the bound
				for (int i = current.level + 2; i < totalItems; i++)
				{
					remaining.push_back(items[i]);
				}
				/*
				Each valid node creates two new nodes -- one with the next item added and one that's a copy of the 
				current node, but its level will be one higher.
				*/
				node node1 = node(current.weight + items[current.level + 1].first, current.price + items[current.level + 1].second, current.level + 1, 0.0);
				node node2 = node(current.weight, current.price, current.level + 1, 0.0);

				// calulate the bounds for each new node
				node1.bound = findBound(node1.price, node1.weight, capacity, remaining);
				node2.bound = findBound(node2.price, node2.weight, capacity, remaining);

				// set the parents for these nodes
				node1.parents = current.parents;
				node1.parents.push_back(current.level + 1); // it uses this item, so we need to add that parent
				node2.parents = current.parents; // doesn't add any new items, so leave it the same

				// enqueue both nodes, even if they'll eventually be skipped
				queue.push_back(node1);
				queue.push_back(node2);
			}
			else // we reached the end of the items, so this must a leaf
			{
				visitedLeaf++;
			}
		}
		else // this node isn't valid, so no nodes are created, and is therefore a leaf
		{
			visitedLeaf++;
		}
	}

	// the following the prints the information to the output stream.
	output << totalItems << "," << currentBestNode.price << "," << currentBestNode.parents.size() << endl;
	output << visitedTotal << "," << visitedLeaf << endl;
	for (int m: currentBestNode.parents)
	{
		output << items[m].first << "," << items[m].second << endl;
	}
	// close the stream
	output.close();
	return 0;
}
