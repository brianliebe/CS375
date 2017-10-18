#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

string getFirstLine(string filename)
{
    // Just reads the file and takes the first line (since the first line is the sequence).
    ifstream infile(filename); // The stream for the input file
    string line; // The first line of the file
    
    if (infile.good())
    {
        getline(infile, line);
    }
    infile.close();

    return line;
}

// This will recursively call, each time decrementing both/either i and/or j to find smaller and smaller LCS's.
int findMaxLCS(string x, string y, int i, int j) 
{
    // Recursively calls the function to find the max LCS length
    if (i < 0 || j < 0) return 0;
    if (x[i] == y[j]) // If there's a match, use the diagonal and add 1
    {
        return 1 + findMaxLCS(x, y, i - 1, j - 1);
    }
    else // If it's not a match, use the max of i-1 or j-1
    {
        return max(findMaxLCS(x, y, i, j - 1), findMaxLCS(x, y, i - 1, j));
    }
}

int main(int argc, char * argv[])
{
    clock_t c1, c2; // The clocks to determine algorithm time
    c1 = clock();

    string inputx(argv[1]); // filex
    string inputy(argv[2]); // filey
    string outputfile(argv[3]); // output file
    ofstream output(outputfile); // the stream to the output so that output << "" can be used

    // Reads the files and finds the corresponding sequences which are saved as strings
    string xsequence = getFirstLine(inputx);
    string ysequence = getFirstLine(inputy);

    // m = length of x, n = length of y.
    int m(xsequence.length());
    int n(ysequence.length());

    string maxLCS(to_string(findMaxLCS(xsequence, ysequence, m - 1, n - 1)));
    c2 = clock();

    // Find the clock difference
    float difference(((float)c2 - (float)c1)/CLOCKS_PER_SEC);
    
    output << maxLCS << endl;
    output << difference << endl;

    return 0;
}