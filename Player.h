/*
Player has a pod. Player will be a virtual class and derived classes will be players
with different strategies.
*/

#include "Pod.h"
#include "Unit.h"
#include <string>
#include <vector>
#include <algorithm>

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

    //Returns player's pod
    Pod getPod();

    //Returns player's name
    const std::string getName() const;

    //Function to build a unit and add to player's inactiveUnits vector
    void buildUnit(const int index);

    //Function to activate a unit, moves it from inactiveUnits to units
    void activateUnit(Unit &unit);

    //Function to destroy an inactive unit, and return its bricks to the player's pod
    void removeInactiveUnit(const Unit &unit);

    //Function to destroy a unit, and return its bricks to the player's pod
    void removeUnit(Unit &unit);

    //Function to remove bricks from pod given a unit
    void useBricks(const Unit &unit);

    //Function to remove bricks from pod for repairing. Uses only bricks required to level up
    void useBricks(const Unit &unit, const int levels);

    //Function to return bricks needed for input unit to go from current level-1 to current level
    void returnBricks(const Unit &unit);

    //Returns units vector
    std::vector<Unit> getUnits() const;

    //Prints out active units and indices for selection
    void printActive() const;

    //Prints out inactive units and indices for selection
    void printInactive() const;

    //Pushes input unit into player's units vector
    void addUnit(const Unit &unit);

    //Returns inactive units vector
    std::vector<Unit> getInactiveUnits() const;

    //Pushes input unit into player's inactive units vector
    void addInactiveUnit(const Unit &unit);

    //Function that finds an inactive unit and returns index
    int findInactiveUnit(const Unit &unit);

    //Function that finds an active unit and returns index
    int findUnit(const Unit &unit);

    //Function to determine if there is more than one of a unit type
    const bool duplicateUnits(const Unit &unit);

    //Print out plansheet, add a * in front of units that player do not have enough bricks for
    void printPlanSheet();

private:
    std::string name;   //Player's name
    Pod pod;        //Player's pod
    std::vector<Unit> units;    //Player's active units
    std::vector<Unit> inactiveUnits;    //Units that player has yet to place on board
};
