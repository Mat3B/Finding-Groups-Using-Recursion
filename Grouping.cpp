/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{}, groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for (int g = 0; g < groups.size(); g++)
    {
        cout << "Group " << g + 1 << ": ";
        for (int s = 0; s < groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}

// getting strange warning with this Grouping::Grouping saying that grid is not initialized. but everything still works 
Grouping::Grouping(string filename) {

    string fileInput;                       // create string called file input
    ifstream input(filename);               // use this string with ifstream to get input from fies

    vector<GridSquare> Storage;             // create a vector of GridSquare called storage

    for (int i = 0; i < 10; i++) {

        getline(input, fileInput);          // get the input from the ifstream 
            
        for (int j = 0; j < 10; j++) {  

            if (fileInput[j] == 'X') {      // if the file input is equal to an X then that point is set equal to 1

                grid[i][j] = 1;

            }

            else if (fileInput[j] == '.') { // if the file input is equal to an . then that point is set equal to 0

                grid[i][j] = 0;

            }

        }

    }

    for (int x = 0; x < 10; x++) {

        for (int y = 0; y < 10; y++) {

            if (grid[x][y] == 1) {          // if statement if the grid is equal to the value of one

                groups.push_back(Storage);  // pushes this back to storage and calls find group 
                findGroup(x, y);            // calls  with x, y

            }
        }
    }

}

void Grouping::findGroup(int r, int c) {

    if (grid[r][c] == 0) {                  // if it is 0 (empty) returns 

        return;

    }

    grid[r][c] = 0;

    int higherBound = 10;
    int lowerBound = 0;

    groups.back().push_back(GridSquare(r, c));  // pushing back the gridSquare using r, c

    if ((r + 1) < higherBound) {                // if statement for if r + 1 is < than higher bound 

        findGroup(r + 1, c);

    }

    if ((r - 1) >= lowerBound) {                // if statement for if r - 1 is >= than lower bound 

        findGroup(r - 1, c);

    }

    if ((c + 1) < higherBound) {                // if statement for if c + 1 is < than higher bound 

        findGroup(r, c + 1);

    }

    if ((c - 1) >= lowerBound) {                // if statement for if c - 1 is >= than higher bound 

        findGroup(r, c - 1);

    }
}