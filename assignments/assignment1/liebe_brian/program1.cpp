#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int MAX_SEQUENCE_SIZE = 10; // Just a testing variable, it determines when to print a full array
string SEPARATOR_CHAR = "-"; // Used for splitting the value/arrow for the array
string STOP_CHAR = "s";
string DIAG_CHAR = "d";
string UP_CHAR = "u";
string LEFT_CHAR = "l";

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

int main(int argc, char * argv[])
{
    clock_t c1, c2; // Clocks for algorithm timing
    c1 = clock();

    // String inputs from argv for all input/output files
    string inputx(argv[1]);
    string inputy(argv[2]);
    string outputfile(argv[3]);
    ofstream output(outputfile);

    // Reads the files and finds the corresponding sequences.
    string xsequence = getFirstLine(inputx);
    string ysequence = getFirstLine(inputy);

    // m = length of x, n = length of y. Creates two array (for values and for direction).
    int m(xsequence.length());
    int n(ysequence.length());
    int array[m+1][n+1];
    string arrow[m+1][n+1];

    // Set the values for the first row and first column (that are 0's)
    // For the arrow (directional) array, s = stop, d = diagonal, l = left, and u = up.
    for (int i = 0; i < m+1; i++)
    {
        array[i][0] = 0;
        arrow[i][0] = STOP_CHAR;
    }
    for (int i = 0; i < n+1; i++)
    {
        array[0][i] = 0;
        arrow[0][i] = STOP_CHAR;
    }

    // Check for a match, if yes then increment by 1 and use diagonal. Otherwise pick max of 2 adjacent spots.
    for (int i = 1; i < m + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            if (xsequence[i-1] == ysequence[j-1])
            {
                array[i][j] = 1 + array[i-1][j-1];
                arrow[i][j] = DIAG_CHAR; // uses the diagonal value
            }
            else
            {
                int a = array[i-1][j];
                int b = array[i][j-1];

                if (a > b)
                {
                    array[i][j] = a;
                    arrow[i][j] = UP_CHAR; // uses the upper value
                }
                else if (b > a)
                {
                    array[i][j] = b;
                    arrow[i][j] = LEFT_CHAR; // uses the left value
                }
                else
                {
                    array[i][j] = b;
                    arrow[i][j] = LEFT_CHAR; // defaults to the left value
                }
            }
        }
    }
    c2 = clock();

    // If m and n are less than/equal to 10, then it prints the full array.
    if (m <= MAX_SEQUENCE_SIZE && n <= MAX_SEQUENCE_SIZE)
    {
        for (int j = 0; j < n + 1; j++)
        {
            output << "0" + SEPARATOR_CHAR + STOP_CHAR + "  ";
        }
        output << endl;
        for (int i = 1; i < m+1; i++)
        {
            output << "0" + SEPARATOR_CHAR + STOP_CHAR + "  ";
            for (int j = 1; j < n + 1; j++)
            {
                output << to_string(array[i][j]) + SEPARATOR_CHAR + arrow[i][j] + "  ";
            }
            output << "" << endl;
        }

        // Find the maximum case by moving backwards
        string final = "";
        int done = 0;
        while (!done)
        {
            string curr = arrow[m][n];
            if (curr == DIAG_CHAR)
            {
                final += xsequence[m-1];
                m--;
                n--;
            }
            else if (curr == UP_CHAR) m--;
            else if (curr == LEFT_CHAR) n--;
            else done = 1;
        }

        // Reverse the order of the string and print it.
        for (int i = final.length() - 1; i >= 0; i--) output << final[i];
        output << endl;
    }
    else
    {
        // Print just the max size (which is at [m][n]).
        output << array[m][n] << endl;
    }

    // Find the clock difference
    float difference(((float)c2 - (float)c1)/CLOCKS_PER_SEC);
    output << difference << endl;
    return 0;
}
