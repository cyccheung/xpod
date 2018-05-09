#ifndef POD_H
#define POD_H

/*
There are 8 pods (factions): Aero, Auto, Robo, Wild, Dragon, Monster, Arachno, Aqua
Each faction has a different inventory. A faction is a derived class of Pod.
A Pod object has a vector of ints as a private member variable. All the pieces used in
this game has an index from 1-43 (1-43 in code as well, index 0 will be 0 as placeholder).
As pieces are used and returned, this vector is updated as needed.
*/

#include "Piece.h"
#include <string>
#include <vector>

class Pod {
public:
    //Pod default constructor creates a Pod with an empty inventory. Should never be used.
    //Pod();

    //Pod constructor creates a Pod with the parts provided in the argument
    Pod(const std::string nameIn);

    //Returns name of pod (i.e Aero)
    const std::string getName() const;

    //Prints inventory in order from 0-42. Prints in the following format:
    //1, 2, 3, 4, ... 41, 42, 43
    const void printInventory() const;

    //Function to add specified piece into pod
    void addPiece(const int partIndex);

    //Function to remove specified piece from pod
    void removePiece(const int partIndex);

    //Print plan sheet. Consider another method of printing out plan sheet
    //virtual const void printPlanSheet() const = 0;
private:
    //Vector of ints as inventory
    std::vector<int> inventory;
    //Name of faction
    std::string factionName;
};

#endif
