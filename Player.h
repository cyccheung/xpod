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

    //Returns player's pod
    const Pod getPod() const;

    //Function to build a unit and return it by reference
    void buildUnit(const std::string &unitName);

    //Function to activate a unit, moves it from inactiveUnits to units
    void activateUnit(Unit &unit);

    //Function to destroy an inactive unit, and return its bricks to the player's pod
    void removeInactiveUnit(const Unit &unit);

    //Function to destroy a unit, and return its bricks to the player's pod
    void removeUnit(Unit &unit);

    //Function to remove bricks from pod given a unit
    void useBricks(const Unit &unit);

    //Function to return bricks making up unit to pod
    void returnBricks(const Unit &unit);

    //Returns units vector
    std::vector<Unit> getUnits();

    //Pushes input unit into player's units vector
    void addUnit(const Unit &unit);

    //Returns inactive units vector
    std::vector<Unit> getInactiveUnits();

    //Pushes input unit into player's inactive units vector
    void addInactiveUnit(const Unit &unit);

    //Function that finds an inactive unit and returns index
    int findInactiveUnit(const Unit &unit);

    //Function that finds an active unit and returns index
    int findUnit(const Unit &unit);

private:
    std::string name;   //Player's name
    Pod pod;        //Player's pod
    std::vector<Unit> units;    //Player's active units
    std::vector<Unit> inactiveUnits;    //Units that player has yet to place on board
};
