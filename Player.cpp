#include "Player.h"
#include <iostream>     //Debugging purposes

const bool Player::enoughBricks(const Unit &unit) {
    //Use up bricks as if there are enough
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        pod.removeBrickSpecial(unit.getBricks().at(i));
    }
    //Loops through inventory to look for negative numbers, if found, not enough bricks
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        if(pod.getInventory().at(unit.getBricks().at(i)) < 0) {
            //Add bricks back into inventory before returning
            for(int j = 0; j < (int)unit.getBricks().size(); ++j) {
                pod.addBrick(unit.getBricks().at(j));
            }
            return false;
        }
    }
    //Add bricks back into inventory before returning
    for(int j = 0; j < (int)unit.getBricks().size(); ++j) {
        pod.addBrick(unit.getBricks().at(j));
    }
    //Otherwise return true
    return true;
}

const Pod Player::getPod() const {
    return pod;
}

void Player::buildUnit(const std::string &unitName) {
    //Create default unit
    Unit unit;
    //Figure out which constructor to call
    if(unitName == "AirCab") {
        AirCab tempUnit;
        unit = tempUnit;
    }
    else if(unitName == "AirScout") {
        AirScout tempUnit;
        unit = tempUnit;
    }
    //Use up appropriate bricks
    useBricks(unit);
    //Add unit to vector of inactive units
    inactiveUnits.push_back(unit);
}

void Player::activateUnit(Unit &unit) {
    //Adds unit to active units vector
    units.push_back(unit);
    //Finds unit's index
    int index = findInactiveUnit(unit);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeInactiveUnit(const Unit &unit) {
    //Finds unit's index
    int index = findInactiveUnit(unit);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        //Returns unit's bricks to inventory
        returnBricks(unit);
        //Removes unit from inactive units vector
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeUnit(Unit &unit) {
    //Finds unit's index
    int index = findUnit(unit);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        //Returns unit's bricks to inventory
        returnBricks(unit);
        //Removes unit from units vector
        units.erase(units.begin() + index);
    }
}

void Player::useBricks(const Unit &unit) {
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        pod.removeBrick(unit.getBricks().at(i));
    }
}

void Player::returnBricks(const Unit &unit) {
    std::vector<int> tempBricks;
    for(int i = 0; i < unit.getLevelBricks(unit.getLevel()); ++i) {
        tempBricks.push_back(unit.getBricks().at(i));
    }
    for(int i = 0; i < (int)tempBricks.size(); ++i) {
        pod.addBrick(tempBricks.at(i));
    }
}

std::vector<Unit> Player::getUnits() {
    return units;
}

void Player::addUnit(const Unit &unit) {
    units.push_back(unit);
}

std::vector<Unit> Player::getInactiveUnits() {
    return inactiveUnits;
}

void Player::addInactiveUnit(const Unit &unit) {
    inactiveUnits.push_back(unit);
}

int Player::findInactiveUnit(const Unit &unit) {
    for(int i = 0; i < (int)inactiveUnits.size(); ++i) {
        if(unit.getPosition() == inactiveUnits.at(i).getPosition()) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}

int Player::findUnit(const Unit &unit) {
    for(int i = 0; i < (int)units.size(); ++i) {
        if(unit.getPosition() == units.at(i).getPosition()) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}
