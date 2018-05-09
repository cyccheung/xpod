/*
Player has a pod. Player will be a virtual class and derived classes will be players
with different strategies
*/

#include "Pod.h"
#include "Unit.h"
#include <string>
#include <vector>

class Player {
public:
    //Default constructor creates player with Aero
    Player()
        : pod(Pod("Aero")) {}
    //Player constructor creates player with chosen pod
    Player(const std:string pod_in)
        : pod(Pod(pod_in)) {}

    //Function to figure out if player has enough pieces to build unit

    //Function to build a unit, store it into inactiveUnits, and uses up bricks in pod

    //Function to activate a unit, moves it from inactiveUnits to units
private:
    std::string name;   //Player's name
    Pod pod;        //Player's pod
    std::vector<Unit> units;    //Player's active units
    std::vector<Unit> inactiveUnits;    //Units that player has yet to place on board
};
