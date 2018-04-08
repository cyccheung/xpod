#ifndef POD_H
#define POD_H

/*
There are a total of 8 pods: Aero, Auto, Robo, Wild, Dragon, Monster, Arachno, Aqua
Each pod has a different inventory. Each pod is a derived class of Pod.
A Pod object has a vector of ints as a private member variable. All the pieces used in
this game has an index from 1-43 (0-42 in code). As pieces are used and returned,
this vector is updated as needed.
*/

#include "Piece.h"
#include <string>
#include <vector>

class Pod {
public:
    //Pod default constructor creates a Pod with an empty inventory. Should never be used.
    Pod();

    //Pod constructor creates a Pod with the parts provided in the argument
    Pod(const std::vector<int> inventoryInput);

    //Returns name of pod (i.e Aero)
    virtual const std::string getName() const = 0;

    //Prints inventory in order from 0-42. Prints in the following format:
    //1, 2, 3, 4, ... 41, 42, 43
    const void printInventory() const;
private:
    //Vector of ints as inventory
    std::vector<int> inventory;
};

#endif
