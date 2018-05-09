#include "Arena.h"
#include <iostream>

//Default constructor creates 9x6 arena
Arena::Arena()
    : length(9), width(6) {}

//Custom constructor creates specified arena
Arena::Arena(const int lengthIn, const int widthIn)
    : length(lengthIn), width(widthIn) {}

//Returns whether the specified position is obstacle free
bool Arena::openSquare(const int &row, const int &column) {
    for(int i = 0; i < obstacles.size(); ++i) {
        if(obstacles.at(i).first == row && obstacles.at(i).second == column) {
            return false;
        }
    }
    return true;
}

//Print out obstacles in the following format:
/*
2 5     //Row 2, column 5
3 1     //Row 3, column 1
*/
const void Arena::printObstacles() {
    for(int i = 0; i < obstacles.size(); ++i) {
        std::cout << obstacles.at(i).first << " " << obstacles.at(i).second << "\n"
    }
}
