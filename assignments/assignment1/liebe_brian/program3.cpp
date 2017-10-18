#include <iostream>
#include <fstream>
#include <time.h>
#include <limits>

using namespace std;

int ** array; // 2D array used to store the memoized values 

string getFirstLine(string filename)
{
    // Just reads the file and takes the first line (since the first line is the sequence).
    ifstream infile(filename);
    string line;
    
    if (infile.good())
    {
        getline(infile, line);
    }
    infile.close();

    return line;
}

int findMaxLCS(string x, string y, int i, int j) 
{
    // Checks the base case of i or j < 0, which will just return 0
    if (i < 0 || j < 0)
    {
        return 0;
    }
    // Checks to see if the value has been assigned
    if (array[i][j] == (-1) * numeric_limits<int>::max())
    {
        // If there's a match, add one to the running total. Otherwise, choose the max of the top and left
        if (x[i] == y[j])
        {
            array[i][j] = 1 + findMaxLCS(x, y, i - 1, j - 1);
        }
        else 
        {
            array[i][j] = max(findMaxLCS(x, y, i - 1, j), findMaxLCS(x, y, i, j - 1));
        }
    }
    // Return the max for this location
    return array[i][j];
}

int main(int argc, char * argv[])
{
    clock_t c1, c2; // Clocks for finding algorithm run time
    c1 = clock();

    // Each input/output file will be read from argv and saved to strings
    // A stream for the output file is created
    string inputx(argv[1]);
    string inputy(argv[2]);
    string outputfile(argv[3]);
    ofstream output(outputfile);

    // Reads the files and finds the corresponding sequences
    string xsequence = getFirstLine(inputx);
    string ysequence = getFirstLine(inputy);

    // m = length of x, n = length of y
    int m(xsequence.length());
    int n(ysequence.length());

    // Set all the values in the array to negative infinity.
    array = new int * [m+1];
    for (int i = 0; i < m + 1; i++)
    {
        array[i] = new int[n+1];
        for (int j = 0; j < n + 1; j++) 
        {
            array[i][j] = (-1) * numeric_limits<int>::max();
        }
    }

    // Output the max value
    output << to_string(findMaxLCS(xsequence, ysequence, m - 1, n - 1)) << endl;

    c2 = clock();

    // Find the clock difference
    float difference(((float)c2 - (float)c1)/CLOCKS_PER_SEC);
    output << difference << endl;
    return 0;
}