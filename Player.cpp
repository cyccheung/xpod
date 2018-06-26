#include "Player.h"

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

const bool Player::enoughBricksRepair(const Unit &unit, const int repairedLevel) {
    //Use up bricks as if there are enough
    for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
        pod.removeBrickSpecial(unit.getBricks().at(i));
    }
    //Loops through inventory to look for negative numbers, if found, not enough bricks
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        if(pod.getInventory().at(unit.getBricks().at(i)) < 0) {
            //Add bricks back into inventory before returning
            for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
                pod.addBrick(unit.getBricks().at(i));
            }
            return false;
        }
    }
    //Add bricks back into inventory before returning
    for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
        pod.addBrick(unit.getBricks().at(i));
    }
    //Otherwise return true
    return true;
}

Pod* Player::getPod() {
    return &pod;
}

const std::string Player::getName() const {
    return name;
}

void Player::buildUnit(const int index) {
    if(pod.getName() == "Aero") {
        if(index == 0) {
            AirCab* aircab = new AirCab;
            inactiveUnits.push_back(aircab);
        }
        else if(index == 1) {
            AirScout* airscout = new AirScout;
            inactiveUnits.push_back(airscout);
        }
    }
    else if(pod.getName() == "Auto") {
        if(index == 0) {
            Dozer* dozer = new Dozer;
            inactiveUnits.push_back(dozer);
        }
    }
}

void Player::activateUnit(Unit* unitPtr) {
    //Adds unit to active units vector
    units.push_back(unitPtr);
    //Finds unit's index
    int index = findInactiveUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeInactiveUnit(Unit* unitPtr) {
    //Finds unit's index
    int index = findInactiveUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        //Returns unit's bricks to inventory
        returnBricks(unitPtr);
        delete inactiveUnits.at(index);
        //Removes unit from inactive units vector
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeUnit(Unit* unitPtr) {
    //Finds unit's index
    int index = findUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        for(int i = 0; i < unitPtr->getLevel(); ++i) {
            //Returns unit's bricks to inventory
            returnBricks(unitPtr);
            //Lower's unit's level by one
            unitPtr->setLevel(unitPtr->getLevel() - 1);
        }
        delete units.at(index);
        //Removes unit from units vector
        units.erase(units.begin() + index);
    }
}

void Player::useBricks(Unit* unitPtr) {
    for(int i = 0; i < (int)unitPtr->getBricks().size(); ++i) {
        pod.removeBrick(unitPtr->getBricks().at(i));
    }
}

void Player::useBricks(Unit* unitPtr, const int levels) {
    for(int i = unitPtr->getLevelBricks(unitPtr->getLevel()); i < unitPtr->getLevelBricks(unitPtr->getLevel() + levels); ++i) {
        pod.removeBrick(unitPtr->getBricks().at(i));
    }
}

void Player::returnBricks(Unit* unitPtr) {
    std::vector<int> tempBricks;
    for(int i = unitPtr->getLevelBricks(unitPtr->getLevel() - 1); i < unitPtr->getLevelBricks(unitPtr->getLevel()); ++i) {
        tempBricks.push_back(unitPtr->getBricks().at(i));
    }
    for(int i = 0; i < (int)tempBricks.size(); ++i) {
        pod.addBrick(tempBricks.at(i));
    }
}

std::vector<Unit*> Player::getUnits() const {
    return units;
}

Unit* Player::getUnit(const int index) {
    return units.at(index);
}

void Player::printActive() const {
    std::cout << "Active units:\n";
    for(int i = 0; i < (int)units.size(); ++i) {
        std::cout << "[" << i << "]\n";
        units.at(i)->printInfo();
    }
}

void Player::printInactive() const {
    std::cout << "Inactive units:\n";
    for(int i = 0; i < (int)inactiveUnits.size(); ++i) {
        std::cout << "[" << i << "]\n";
        inactiveUnits.at(i)->printInfo();
    }
}

void Player::addUnit(Unit* unitPtr) {
    units.push_back(unitPtr);
}

std::vector<Unit*> Player::getInactiveUnits() const {
    return inactiveUnits;
}

Unit* Player::getInactiveUnit(const int index) {
    return inactiveUnits.at(index);
}

void Player::addInactiveUnit(Unit* unitPtr) {
    inactiveUnits.push_back(unitPtr);
}

int Player::findInactiveUnit(Unit* unitPtr) {
    for(int i = 0; i < (int)inactiveUnits.size(); ++i) {
        if(unitPtr == inactiveUnits.at(i)) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}

int Player::findUnit(Unit* unitPtr) {
    for(int i = 0; i < (int)units.size(); ++i) {
        if(unitPtr == units.at(i)) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}

const bool Player::duplicateUnits(Unit* unitPtr) {
    //If any of the other units have the same name, return true
    for(int i = 0; i < (int)units.size(); ++i) {
        //Makes sure to not check itself
        if(units.at(i)->getName() == unitPtr->getName() && units.at(i) != unitPtr) {
            return true;
        }
    }
    return false;
}

void Player::printPlanSheet() {
    for(int i = 0; i < (int)pod.getPlanSheet().size(); ++i) {
        //If not enough bricks to build, add a *
        if(!enoughBricks(pod.getPlanSheet().at(i))) {
            std::cout << "*";
        }
        std::cout << "[" << i << "] ";
        pod.getPlanSheet().at(i).printInfo();
        std::cout << "\n";
    }
}

void Player::setActivePosition(const int choice, const std::pair<int,int> &position) {
    units.at(choice)->setPosition(position);
}

void Player::setInactivePosition(const int choice, const std::pair<int,int> &position) {
    inactiveUnits.at(choice)->setPosition(position);
}
