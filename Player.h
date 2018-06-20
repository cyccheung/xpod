/*
Player has a pod. Player will be a virtual class and derived classes will be players
with different strategies.
*/

#include "Pod.h"
#include "Unit.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Player {
public:
    //Default constructor creates player with Aero
    Player()
        : pod(Pod("Aero")) {}
    //Player constructor creates player with chosen pod
    Player(const std::string nameIn, const std::string pod_in)
        : name(nameIn), pod(Pod(pod_in)) {}

    //Function to figure out if player has enough bricks to build unit
    const bool enoughBricks(const Unit &unit);

    //Function to figure out if player has enough bricks to repair unit from level x-1 to x
    const bool enoughBricksRepair(const Unit &unit, const int repairedLevel);

    //Returns pointer to player's pod
    Pod* getPod();

    //Returns player's name
    const std::string getName() const;

    //Function to build a unit and add to player's inactiveUnits vector
    void buildUnit(const int index);

    //Function to activate a unit, moves it from inactiveUnits to units
    void activateUnit(Unit* unitPtr);

    //Function to destroy an inactive unit, and return its bricks to the player's pod
    void removeInactiveUnit(Unit* unitPtr);

    //Function to destroy a unit, and return its bricks to the player's pod
    void removeUnit(Unit* unitPtr);

    //Function to remove bricks from pod given a unit
    void useBricks(Unit* unitPtr);

    //Function to remove bricks from pod for repairing. Uses only bricks required to level up
    void useBricks(Unit* unitPtr, const int levels);

    //Function to return bricks needed for input unit to go from current level-1 to current level
    void returnBricks(Unit* unitPtr);

    //Returns units vector
    std::vector<Unit> getUnits() const;

    //Returns pointer to active unit by index
    Unit* getUnit(const int index);

    //Prints out active units and indices for selection
    void printActive() const;

    //Prints out inactive units and indices for selection
    void printInactive() const;

    //Pushes input unit into player's units vector
    void addUnit(Unit* unitPtr);

    //Returns inactive units vector
    std::vector<Unit> getInactiveUnits() const;

    //Returns pointer to inactive unit by index
    Unit* getInactiveUnit(const int index);

    //Pushes input unit into player's inactive units vector
    void addInactiveUnit(Unit* unitPtr);

    //Function that finds an inactive unit and returns index
    int findInactiveUnit(Unit* unitPtr);

    //Function that finds an active unit and returns index
    int findUnit(Unit* unitPtr);

    //Function to determine if there is more than one of a unit type
    const bool duplicateUnits(Unit* unitPtr);

    //Print out plansheet, add a * in front of units that player do not have enough bricks for
    void printPlanSheet();

    //Set active unit position
    void setActivePosition(const int choice, const std::pair<int,int> &position);

    //Set inactive unit position
    void setInactivePosition(const int choice, const std::pair<int,int> &position);

private:
    std::string name;   //Player's name
    Pod pod;        //Player's pod
    std::vector<Unit> units;    //Player's active units
    std::vector<Unit> inactiveUnits;    //Units that player has yet to place on board
};
