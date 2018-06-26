#ifndef ARENA_H
#define ARENA_H

/*
Arena size can be specified but the standard arena is 9 long x 6 wide (including home row)
Default constructor creates 9x6 arena. Custom constructor takes in rows x columns.
Maximum size set as 27 long x 12 wide.
Stores obstacles as a vector of pairs. Each pair contains the <row, column> of each
obstacle.
Bottom left position is (0,0).
Player 1 home row is row 0 and Player 2's is row length (member variable)
*/

#include <vector>

class Arena {
public:
    //Default constructor creates 9x6 arena
    Arena();

    //Custom constructor creates specified arena
    Arena(const int &lengthIn, const int &widthIn);

    //Returns whether the specified position is obstacle free
    bool openSquare(const std::pair<int,int> &position) const;

    //Print out obstacles in the following format:
    /*
    2 5     //Row 2, column 5
    3 1     //Row 3, column 1
    */
    const void printObstacles();

    //Returns vector of obstacles
    std::vector<std::pair<int, int> > getObstacles() const;

    //Returns whether or not position is an opponent home row. player input parameter
    //is the player whose turn it is, is true if player 1, false if player 2
    const bool ifHome(const std::pair<int,int> &position, const bool player);

    //Returns whether or not position is edge of map. Returns true for positions outside the arena
    //Returns false for positions on the border (i.e 0,0 and 3,2 will return false for a 4x3 arena)
    const bool edgeOfMap(const std::pair<int,int> &position) const;

    //Returns number of rows
    int getRows() const;

    //Returns numbers of columns
    int getColumns() const;

    //Returns if position is inside the arena
    const bool inArena(const std::pair<int,int> &position) const;

private:
    int length; //Rows
    int width;  //Columns
    std::vector<std::pair<int, int> > obstacles;
};

#endif
