#ifndef PIECE_H
#define PIECE_H

/*
An individual lego piece. Has an index in inventory.
*/

#include <string>
#include <cassert>

class Piece {
public:
    //Returns index of piece from inventory (1-43) makes it easier for players
    const std::string getName() const = 0;

private:
    int index;  //Index in inventory
};

#endif
