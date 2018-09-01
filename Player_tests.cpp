#include "Player.h"
#include "Pod.h"
#include "Unit.h"
#include <cassert>
#include <iostream>

using namespace std;

//Tests basic player ctor
void testCtor() {
    Player player1("Bob", "Aero");
    vector<Unit> testUnits;
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        assert(testUnits.at(i) == player1.getUnits().at(i));
    }
    assert(testUnits == player1.getUnits());
    assert(testUnits == player1.getInactiveUnits());
    cout << "testCtor pass\n";
}

//Tests printing inventory
void testInventory() {
    Player player1("Bob", "Aero");
    player1.getPod().printInventory();
}

//Tests building an AirCab
void testBuild() {
    Player player1("Bob", "Aero");
    player1.buildUnit(0);
    player1.getInactiveUnits().at(0).printInfo();
    cout << "testBuild end\n";
}

//Tests if enoughBricks, basic case
void testEnoughBricks1() {
    Player player1("Bob", "Aero");
    AirCab unit;
    assert(player1.enoughBricks(unit));
    player1.buildUnit(0);
    assert(!player1.enoughBricks(unit));
    cout << "testEnoughBricks1 pass\n";
}

//Tests if enoughBricks reverts the inventory after calculations
void testEnoughBricks2() {
    Player player1("Bob", "Aero");
    AirCab unit;
    assert(player1.enoughBricks(unit));
    assert(player1.enoughBricks(unit));
    player1.buildUnit(0);
    assert(!player1.enoughBricks(unit));
    cout << "testEnoughBricks2 pass\n";
}

//Tests activating a unit after building one unit
void testActivate1() {
    Player player1("Bob", "Aero");
    player1.buildUnit(0);
    assert(player1.getInactiveUnits().at(0).getName() == "AirCab");
    assert(player1.getUnits().size() == 0);
    player1.activateUnit(player1.getInactiveUnits().at(0));
    assert(player1.getUnits().at(0).getName() == "AirCab");
    assert(player1.getInactiveUnits().size() == 0);
    cout << "testActivate1 pass\n";
}

//Tests activating a unit after building two units
void testActivate2() {
    Player player1("Bob", "Aero");
    player1.buildUnit(0);
    player1.buildUnit(1);
    assert(player1.getInactiveUnits().at(0).getName() == "AirCab");
    assert(player1.getInactiveUnits().at(1).getName() == "AirScout");
    assert(player1.getUnits().size() == 0);
    player1.activateUnit(player1.getInactiveUnits().at(0));
    assert(player1.getUnits().at(0).getName() == "AirCab");
    assert(player1.getInactiveUnits().size() == 1);
    cout << "testActivate2 pass\n";
}

//Tests building an destroying an inactive unit
void testRemove1() {
    Player player1("Bob", "Aero");
    player1.buildUnit(0);
    assert(player1.getInactiveUnits().size() == 1);
    assert(!player1.enoughBricks(player1.getPod().getPlanSheet().at(0)));
    player1.removeInactiveUnit(player1.getInactiveUnits().at(0));
    assert(player1.enoughBricks(player1.getPod().getPlanSheet().at(0)));
    assert(player1.getInactiveUnits().size() == 0);
    cout << "testRemove1 pass\n";
}

//Tests removing a unit that has another of the same type in the game by building two
//AirCabs, one in player's inactive units vector and one by itself
//Removes solitary AirCab to check if player still has his AirCab.
void testRemove2() {
    Player player1("Bob", "Aero");
    AirCab unit;
    unit.setPosition(1, 1);
    player1.buildUnit(0);
    assert(player1.getInactiveUnits().size() == 1);
    assert(!player1.enoughBricks(player1.getPod().getPlanSheet().at(0)));
    player1.removeInactiveUnit(unit);
    assert(player1.getInactiveUnits().size() == 1);
    assert(!player1.enoughBricks(player1.getPod().getPlanSheet().at(0)));
    cout << "testRemove2 pass\n";
}

//Tests returning bricks to pod
void testReturnBricks() {
    Player player1("Bob", "Aero");
    AirCab unit;
    player1.getPod().printInventory();
    player1.returnBricks(unit);
    player1.getPod().printInventory();
    cout << "testReturnBricks end\n";
}

int main() {
    testCtor();
    //testInventory();  //cout long statement
    //testBuild();
    testEnoughBricks1();
    testEnoughBricks2();    //cout long statement
    testActivate1();
    testActivate2();
    testRemove1();
    testRemove2();
    //testReturnBricks();   //cout long statement
    return 0;
}
