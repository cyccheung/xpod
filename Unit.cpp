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
    std::cout << "Position: " << position.first << ", " << position.second << "\n";
    if(frozen) {
        std::cout << "Frozen\n";
    }
}

const std::string Unit::getName() const {
    return name;
}

const std::string Unit::getMove() const {
    //Nothing complicated here, just lots of formatting
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

const int Unit::getMoveMagnitude() const {
    for(int i = 0; i < 4; ++i) {
        if(movement.at(i) != 0) {
            return movement.at(i);
        }
    }
    return 0;
}

const std::vector<int> Unit::getMovement() const {
    return movement;
}

void Unit::setMove(const std::vector<int> &movementIn) {
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
    //Nothing complicated here, just lots of formatting
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
                abilityOut += "web";
            }
            else if(i == 4) {
                abilityOut += "scare";
            }
            abilityOut += " ";
        }
    }
    return abilityOut;
}

const std::vector<bool> Unit::getAbilities() const {
    return ability;
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
    return ability.at(4);
}

const bool Unit::ifWeb() const {
    return ability.at(3);
}

void Unit::setAbility(const std::vector<bool> &abilityIn) {
    ability = abilityIn;
}

void Unit::setDecon(const std::pair<int,int> &deconIn) {
    decon = deconIn;
}

const std::pair<int,int> Unit::getDeconVect() const {
    return decon;
}

const std::vector<int> Unit::getBricks() const {
    return bricks;
}

void Unit::setBricks(const std::vector<int> &bricksIn) {
    bricks = bricksIn;
}

const int Unit::getLevelBricks(int x) const {
    if(x == 1) {
        return bricks01;
    }
    else if(x == 2) {
        return bricks01 + bricks12;
    }
    else if(x == 3) {
        return bricks01 + bricks12 + bricks23;
    }
    else if(x == 4) {
        return bricks01 + bricks12 + bricks23 + bricks34;
    }
    //Will never reach this statement, just to keep compiler quiet
    return -1;
}

const bool Unit::ifFrozen() const {
    return frozen;
}
/*
virtual void Unit::getDecon() {
    return;
}

//Function to repair unit
virtual void Unit::getRepair() {
    return;
}
*/
void Unit::eat(Unit &unit) {
    //Unit being eaten must be level 1
    assert(unit.getLevel() == 1);
    //Deconstruct enemy
    unit.getDecon();
    //Increase this unit's level by 1
    setLevel(getLevel() + 1);
}

void Unit::freeze() {
    frozen = true;
}

void Unit::unfreeze() {
    frozen = false;
}

const std::pair<int,int> Unit::getPosition() const {
    return position;
}

void Unit::setPosition(const std::pair<int,int> &positionIn) {
    position = positionIn;
}

bool operator==(const Unit &lhs, const Unit &rhs) {
    //TODO: Two inactive units will have the same position and therefore equal
    //according to this criteria below. Improve accordingly
    if(lhs.getPosition() == rhs.getPosition()) {
        return true;
    }
    else {
        return false;
    }
}

bool operator!=(const Unit &lhs, const Unit &rhs) {
    if(lhs.getPosition() != rhs.getPosition()) {
        return true;
    }
    else {
        return false;
    }
}
