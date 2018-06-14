#include "Arena.h"
#include <iostream>

//Default constructor creates 9x6 arena with 3 obstacles at 2,3 3,5 1,6
Arena::Arena()
    : length(9), width(6) {
        std::pair<int,int> obstacle1 = std::make_pair(2,3);
        std::pair<int,int> obstacle2 = std::make_pair(3,5);
        std::pair<int,int> obstacle3 = std::make_pair(1,6);
        obstacles.push_back(obstacle1);
        obstacles.push_back(obstacle2);
        obstacles.push_back(obstacle3);
    }

//Custom constructor creates specified arena
Arena::Arena(const int &lengthIn, const int &widthIn)
    : length(lengthIn), width(widthIn) {}

//Returns whether the specified position is obstacle free
bool Arena::openSquare(const std::pair<int,int> &position) const {
    for(int i = 0; i < (int)obstacles.size(); ++i) {
        if(obstacles.at(i).first == position.first && obstacles.at(i).second == position.second) {
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
    for(int i = 0; i < (int)obstacles.size(); ++i) {
        std::cout << obstacles.at(i).first << " " << obstacles.at(i).second << "\n";
    }
}

std::vector<std::pair<int, int> > Arena::getObstacles() const {
    return obstacles;
}

const bool Arena::ifHome(const std::pair<int,int> &position, const bool player) {
    //If player 1's unit
    if(player) {
        //If unit is in row 8 or more
        if(position.first >= (length - 1)) {
            return true;
        }
    }
    //If player 2's unit
    else {
        //If unit is in row 0 or less
        if(position.first <= 0) {
            return true;
        }
    }
    //Otherwise return false
    return false;
}

const bool Arena::edgeOfMap(const std::pair<int,int> &position) const {
    if(position.first <= -1 || position.first >= length) {
        return true;
    }
    else if(position.second <= -1 || position.second >= width) {
        return true;
    }
    return false;
}


int Arena::getRows() const {
    return length;
}

int Arena::getColumns() const {
    return width;
}
