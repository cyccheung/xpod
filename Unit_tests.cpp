#include "Unit.h"
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;
/*
//Create an Aircab
void testCtor() {
    AirCab unit1;
    //unit1.printInfo();
    assert(unit1.getName() == "AirCab");
    assert(unit1.getMove() == "fly 1");
    //cout << unit1.getAbility() << endl;
    assert(unit1.getAbility() == "carry ");
    assert(unit1.getLevel() == 2);
    assert(unit1.getMaxLevel() == 2);
    vector<int> parts;
    parts.push_back(2);
    parts.push_back(7);
    parts.push_back(4);
    parts.push_back(15);
    assert(unit1.getBricks() == parts);
    assert(unit1.getLevelBricks(1) == 2);
    assert(unit1.getLevelBricks(2) == 4);
    assert(unit1.ifFrozen() == false);
    cout << "testCtor pass\n";
}

//Create an AirCab and an AirScout. Try using AirScout to decon AirCab
void testDeconRepair() {
    AirCab unit1;
    AirScout unit2;
    assert(unit2.getName() == "AirScout");
    assert(unit2.getAbility() == "decon");
    assert(unit2.ifDecon() == true);
    assert(unit1.ifDecon() == false);
    assert(unit1.ifRepair() == false);
    assert(unit2.ifRepair() == false);
    assert(unit1.ifCarry() == true);
    assert(unit2.ifCarry() == false);
    assert(unit1.ifEat() == false);
    assert(unit2.ifEat() == false);
    assert(unit1.ifScare() == false);
    assert(unit2.ifScare() == false);
    assert(unit1.ifWeb() == false);
    assert(unit2.ifWeb() == false);
    assert(unit1.getMove() == "fly 1");
    unit1.getDecon();
    assert(unit1.getMove() == "");
    unit1.getRepair();
    assert(unit1.getMove() == "fly 1");
    cout << "testDecon pass\n";
}

//Create a Hoverall to test more than one ability
void testHoverall() {
    Hoverall unit1;
    //unit1.printInfo();
    assert(unit1.getName() == "Hoverall");
    assert(unit1.getAbility() == "repair carry ");
    assert(unit1.getMove() == "jump 2");
    assert(unit1.getLevel() == 3);
    assert(unit1.getMaxLevel() == 3);
    unit1.getDecon();
    assert(unit1.getMove() == "move 1");
    assert(unit1.getAbility() == "carry ");
    assert(unit1.getLevel() == 2);
    assert(unit1.getMaxLevel() == 3);
    unit1.getRepair();
    assert(unit1.getAbility() == "repair carry ");
    assert(unit1.getMove() == "jump 2");
    assert(unit1.getLevel() == 3);
    assert(unit1.getMaxLevel() == 3);
    cout << "testHoverall pass\n";
}
*/
/*
//Create a defense station to test R2-3
void testDefenseStation() {
    DefenseStation unit1;
    unit1.printInfo();
    assert(unit1.getName() == "DefenseStation");
    assert(unit1.getAbility() == "decon R3");
    assert(unit1.getLevel() == 2);
    assert(unit1.getMove() == "");
}
*/
/*
//Tests moving units around
void testMoving() {
    AirCab unit1;
    assert(unit1.getPosition().first == 0);
    assert(unit1.getPosition().second == 0);
    unit1.setPosition(2,3);
    assert(unit1.getPosition().first == 2);
    assert(unit1.getPosition().second == 3);
    cout << "testMoving pass\n";
}
*/
void testDecon() {
    vector<Unit*> units;
    AirCab unit1;
    units.push_back(&unit1);
    Unit** unitPtr = &(units.at(0));
    (*unitPtr)->getDecon();
    cout << units.at(0)->getLevel() << endl;
    //assert(units.at(0).getLevel() == 1);
    //cout << "testDecon pass\n";
}

int main() {
    //testCtor();
    //testDeconRepair();
    //testHoverall();
    //testDefenseStation();
    //testMoving();
    testDecon();
    return 0;
}
