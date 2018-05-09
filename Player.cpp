#include "Player.h"

const bool Player::enoughBricks(const Unit &unit) const {
    //Loops through bricks needed to build unit, if not enough, return false
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        if(pod.getInventory().at(unit.getBricks().at(i)) == 0) {
            return false;
        }
    }
    //Otherwise return true
    return true;
}

void Player::buildUnit(std::string unitName) {
    //Figure out which constructor to call
    switch(unitName) {
        case "AirCab": AirCab unit; break;
        case "AirScout": AirScout unit; break;
    }
    //Use up bricks from pod
    useBricks(unit);
    //Add unit to vector of inactive units
    inactiveUnits.push_back(unit);
}

void Player::activateUnit(Unit &unit) {
    //Adds unit to active units vector
    units.push_back(unit);
    //Removes unit from inactive vector
    inactiveUnits.erase(std::remove(inactiveUnits.begin(), inactiveUnits.end(), unit),
               inactiveUnits.end());
}

void Player::removeUnit(Unit &unit) {
    //Saves vector of bricks
    std::vector<int> tempBricks;
    tempBricks = unit.getLevelBricks(unit.getLevel());
    //Return bricks to pod
    for(int i = 0; i < (int)tempBricks.size(); ++i) {
        pod.addBrick(tempBricks.at(i));
    }
    //Find unit (possibly more than one of a type, so must differentiate by position)
    for(int i = 0; i < (int)units.size(); ++i) {
        //If unit in units vector and input unit have the same position
        if(units.at(i).getPosition() == unit.getPosition()) {
            //Remove unit from units vector
            units.erase(units.begin() + i);
        }
    }
}

void Player::useBricks(const Unit &unit) {
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        pod.removeBrick(unit.getBricks().at(i));
    }
}
