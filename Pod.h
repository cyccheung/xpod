#ifndef POD_H
#define POD_H

/*
There are 8 pods (factions): Aero, Auto, Robo, Wild, Dragon, Monster, Arachno, Aqua
Each faction has a different inventory. A faction is a derived class of Pod.
A Pod object has a vector of ints as a private member variable. All the Bricks used in
this game has an index from 1-43 (1-43 in code as well, index 0 will be 0 as placeholder).
As Bricks are used and returned, this vector is updated as needed.
*/

#include <string>
#include <vector>
#include "Unit.h"

class Pod {
public:
    //Pod default constructor creates a Pod with an empty inventory. Should never be used.
    //Pod();

    //Pod constructor creates a Pod with the name provided in the argument
    Pod(const std::string nameIn);

    //Pod destructor deletes plan sheet
    ~Pod();

    //Returns name of pod (i.e Aero)
    const std::string getName() const;

    //Prints inventory in order from 1-76. Prints in the following format:
    //1, 2, 3, 4, ... 74, 75, 76
    const void printInventory() const;

    //Returns inventory
    std::vector<int> getInventory() const;

    //Function to add specified brick into pod
    void addBrick(const int brickIndex);

    //Function to remove specified brick from pod
    void removeBrick(const int brickIndex);

    //Return plan sheet
    const std::vector<Unit> getPlanSheet() const;
private:
    std::vector<int> inventory; //Vector of ints as inventory
    std::string factionName;    //Name of faction
    std::vector<Unit> planSheet;    //Vector of all units in faction
};

#endif
