/*
Pod.cpp contains the constructors for the 8 pods. It fills the inventory vector with the
appropriate number of parts. Functions to add and remove a part from the inventory is
implemented here as well
*/

#include "Pod.h"
#include <cassert>

Pod::Pod(const std::string nameIn) {
    //Set pod's name (i.e Aero, Auto...)
    factionName = nameIn;
    //std::vector<int> tempInventory;
    //tempInventory.push_back(0);
    inventory.push_back(0);
    //TODO: Fill in inventory
    if(nameIn == "Aero") {
        inventory.push_back(1); //1
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(2); //15
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //30
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
    }
    else if(nameIn == "Auto") {
        inventory.push_back(1); //1
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1); //5
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(1); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
    }
    else if(nameIn == "Robo") {
        inventory.push_back(0); //1
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(6);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //10
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(6);
        inventory.push_back(4); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1); //20
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //25
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
    }
    else if(nameIn == "Wild") {
        inventory.push_back(0); //1
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(4);
        inventory.push_back(3); //15
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(3);
        inventory.push_back(1); //25
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(6);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
    }
    else if(nameIn == "Dragon") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(3);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(6);
        inventory.push_back(3); //15
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2); //20
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2); //45
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //50
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //55
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //60
        inventory.push_back(6);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0); //70
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
    }
    else if(nameIn == "Monster") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //10
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(4);
        inventory.push_back(4); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //45
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(4); //50
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //55
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //60
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //65
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
    }
    else if(nameIn == "Arachno") {
        inventory.push_back(0); //1
        inventory.push_back(3);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //40
        inventory.push_back(8);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //45
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2); //50
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //55
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(1); //60
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
    }
    else if(nameIn == "Aqua") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(1);
        inventory.push_back(3);
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //45
        inventory.push_back(5);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //50
        inventory.push_back(0);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //55
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(4);
        inventory.push_back(1); //60
        inventory.push_back(5);
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //75
        inventory.push_back(2); //76
    }
}

const std::string Pod::getname() const {
    return factionName;
}

const void Pod::printInventory() const {
    for(int i = 0; i < (int)inventory.size(); ++i) {
        std::cout << inventory.at(i) << ", ";
    }
    std::cout << "\n";
}

void Pod::addBrick(const int partIndex) {
    ++inventory.at(partIndex);
}

void Pod::removeBrick(const int partIndex) {
    assert(inventory.at(partIndex) > 0);
    --inventory.at(partIndex);
}