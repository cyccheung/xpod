#ifndef ARENA_H
#define ARENA_H

/*
Arena size can be specified but the standard arena is 9 long x 6 wide (including home row)
Default constructor creates 9x6 arena. Custom constructor takes in rows x columns.
Maximum size set as 27 long x 12 wide.
Stores obstacles as a vector of pairs. Each pair contains the <row, column> of each
obstacle.
*/

#include <vector>

class Arena {
public:
    //Default constructor creates 9x6 arena
    Arena();

    //Custom constructor creates specified arena
    Arena(const int &lengthIn, const int &widthIn);

    //Returns whether the specified position is obstacle free
    bool openSquare(const int &row, const int &column);

    //Print out obstacles in the following format:
    /*
    2 5     //Row 2, column 5
    3 1     //Row 3, column 1
    */
    const void printObstacles();
private:
    int length; //Rows
    int width;  //Columns
    std::vector<std::pair<int, int> > obstacles;
};

#endif
