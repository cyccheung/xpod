/*
Unit.cpp contains the implementations for the Unit functions.
*/

#include "Unit.h"
#include <vector>
#include <iostream>
#include <cassert>

//Implementations for non virtual functions in Unit.h
const void Unit::printInfo() const {
    std::cout << name << " Level " << level << ":\n";
    std::cout << getMove() << ", " << getAbility() << "\n";
}

const std::string Unit::getName() const {
    return name;
}

const std::string Unit::getMove() const {
    for(int i = 0; i < (int)movement.size(); ++i) {
        if(i == 0 && (movement.at(i) != 0)) {
            return "move " + std::to_string(movement.at(i));
        }
        else if(i == 1 && (movement.at(i) != 0)) {
            return "jump " + std::to_string(movement.at(i));
        }
        else if(i == 2 && (movement.at(i) != 0)) {
            return "fly " + std::to_string(movement.at(i));
        }
        else if(i == 3 && (movement.at(i) != 0)) {
            return "push " + std::to_string(movement.at(i));
        }
    }
    return "";
}

void Unit::setMove(const std::vector<int> &movementIn) {
    /*
    for(int i = 0; i < (int)movement.size(); ++i) {
        movement.at(i) = movementIn.at(i);
    }
    */
    movement = movementIn;
}

const int Unit::getLevel() const {
    return level;
}

void Unit::setLevel(const int levelIn) {
    level = levelIn;
}

const int Unit::getMaxLevel() const {
    return maxLevel;
}

const std::string Unit::getAbility() const {
    std::string abilityOut;
    if(decon.first > 0) {
        abilityOut += "decon";
    }
    if(decon.first > 1) {
        abilityOut += "+1";
    }
    if(decon.second > 1) {
        abilityOut += " R";
        abilityOut += std::to_string(decon.second);
        abilityOut += " ";
    }
    for(int i = 0; i < (int)ability.size(); ++i) {
        if(ability.at(i)) {
            if(i == 0) {
                abilityOut += "repair";
            }
            else if(i == 1) {
                abilityOut += "carry";
            }
            else if(i == 2) {
                abilityOut += "eat";
            }
            else if(i == 3) {
                abilityOut += "scare";
            }
            else if(i == 4) {
                abilityOut += "web";
            }
            abilityOut += " ";
        }
    }
    return abilityOut;
}

const bool Unit::ifDecon() const {
    if(decon.first > 0) {
        return true;
    }
    return false;
}

const bool Unit::ifRepair() const {
    return ability.at(0);
}

const bool Unit::ifCarry() const {
    return ability.at(1);
}

const bool Unit::ifEat() const {
    return ability.at(2);
}

const bool Unit::ifScare() const {
    return ability.at(3);
}

const bool Unit::ifWeb() const {
    return ability.at(4);
}

void Unit::setAbility(const std::vector<bool> &abilityIn) {
    ability = abilityIn;
}

void Unit::setDecon(const std::pair<int,int> &deconIn) {
    decon = deconIn;
}

const std::vector<int> Unit::getBricks() const {
    return bricks;
}

void Unit::setBricks(const std::vector<int> &bricksIn) {
    bricks = bricksIn;
}

const std::vector<int> Unit::getLevelBricks(int x) const {
    std::vector<int> tempBricks;
    //If going from level 0 to 1
    if(x == 1) {
        for(int i = 0; i < bricks01; ++i) {
            tempBricks.push_back(bricks.at(i));
        }
    }
    //If going from level 1 to 2
    else if(x == 2) {
        for(int i = 0; i < bricks12; ++i) {
            tempBricks.push_back(bricks.at(i));
        }
    }
    //If going from level 2 to 3
    else if(x == 3) {
        for(int i = 0; i < bricks23; ++i) {
            tempBricks.push_back(bricks.at(i));
        }
    }
    //If going from level 3 to 4
    else {
        for(int i = 0; i < bricks34; ++i) {
            tempBricks.push_back(bricks.at(i));
        }
    }
    return tempBricks;
}

const bool Unit::ifFrozen() {
    return frozen;
}

void Unit::eat(Unit &unit) {
    //Unit being eaten must be level 1
    assert(unit.getLevel() == 1);
    //Deconstruct enemy
    unit.getDecon();
    //Increase this unit's level by 1
    setLevel(getLevel() + 1);
}

void Unit::freeze(Unit &unit) const {
    unit.frozen = true;
}

const std::pair<int,int> Unit::getPosition() const {
    return position;
}

void Unit::setPosition(int rowIn, int colIn) {
    std::pair<int,int> tempPos = std::make_pair(rowIn, colIn);
    position = tempPos;
}
