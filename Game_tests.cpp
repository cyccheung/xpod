#include "Game.h"
#include <iostream>
#include <cassert>

using namespace std;

void testMoveUnit() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Place AirCab
    pair<int,int> position = make_pair(2,2);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    //Assert position
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position);
    //Move AirCab
    vector<pair<int,int> > path;
    pair<int,int> position1 = make_pair(2,3);
    path.push_back(position1);
    game.moveUnit(game.getPlayer(1)->getUnit(0), path);
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position1);
    pair<int,int> position2 = make_pair(2,4);
    path.push_back(position2);
    game.moveUnit(game.getPlayer(1)->getUnit(0), path);
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position2);
    pair<int,int> position3 = make_pair(2,5);
    path.push_back(position3);
    game.moveUnit(game.getPlayer(1)->getUnit(0), path);
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position3);
    cout << "testMoveUnit pass\n";
}

void testDecon() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Place AirCab
    pair<int,int> position = make_pair(2,2);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position);
    //Move AirCab from inactive to active vector
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    //Deconstruct AirCab
    game.deconUnit(game.getPlayer(1)->getUnit(0), game.getPlayer(1));
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 1);
    cout << "testDecon pass\n";
}

void testAnyWithinRange1() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Build AirScout
    game.getPlayer(1)->buildUnit(1);
    //Place them next to each other
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(2,3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->getInactiveUnit(1)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    assert(game.anyWithinRange(game.getPlayer(1)->getUnit(0), 1) == true);
    cout << "testAnyWithinRange1 pass\n";
}

void testAnyWithinRange2() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Build AirScout
    game.getPlayer(1)->buildUnit(1);
    //Place them 2 spaces away from each other
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(4,4);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->getInactiveUnit(1)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    assert(game.anyWithinRange(game.getPlayer(1)->getUnit(0), 1) == false);
    cout << "testAnyWithinRange2 pass\n";
}

void testPrintWithinRange1() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Build AirScout
    game.getPlayer(2)->buildUnit(1);
    //Place them next to each other
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(2,3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.printUnitsInRange(game.getPlayer(1)->getUnit(0), 1);
    cout << "testPrintWithinRange1 end\n\n";
}

void testPrintWithinRange2() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Build AirScout
    game.getPlayer(2)->buildUnit(1);
    //Place them next to each other
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(3,3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.printUnitsInRange(game.getPlayer(1)->getUnit(0), 2);
    cout << "testPrintWithinRange2 end\n\n";
}

void testPrintWithinRange3() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    //Build AirScout
    game.getPlayer(2)->buildUnit(1);
    //Place them next to each other
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(3,3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.printUnitsInRange(game.getPlayer(1)->getUnit(0), 1);
    cout << "testPrintWithinRange3 end\n\n";
}

void testDestroy1() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,2);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.deconUnit(game.getPlayer(1)->getUnit(0), game.getPlayer(1));
    cout << "testDestroy1 end\n";
}

void testDestroy2() {
    //Create game object
    Game game("Andy", "Aero", "Bob", "Aero", 9, 6);
    //Build AirCab
    game.getPlayer(1)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,2);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.deconUnit(game.getPlayer(1)->getUnit(0), game.getPlayer(1));
    game.deconUnit(game.getPlayer(1)->getUnit(0), game.getPlayer(1));
    cout << "testDestroy2 end\n";
}

void testPush1() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    //Build Dozer
    game.getPlayer(1)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,2);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    vector<pair<int,int> > path;
    pair<int,int> position2 = make_pair(2,3);
    pair<int,int> position3 = make_pair(2,4);
    path.push_back(position2);
    path.push_back(position3);
    game.pushUnit(game.getPlayer(1)->getUnit(0), path, game.getPlayer(1)->getUnit(0));
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position3);
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 3);
    cout << "testPush1 pass\n";
}

void testPush2() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    //Build Dozer
    game.getPlayer(1)->buildUnit(0);
    game.getPlayer(2)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(2,3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    vector<pair<int,int> > path;
    pair<int,int> position3 = make_pair(2,4);
    path.push_back(position2);
    path.push_back(position3);
    pair<int,int> position4 = make_pair(2,5);
    game.pushUnit(game.getPlayer(1)->getUnit(0), path, game.getPlayer(1)->getUnit(0));
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position3);
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 3);
    assert(game.getPlayer(2)->getUnit(0)->getPosition() == position4);
    assert(game.getPlayer(2)->getUnit(0)->getLevel() == 2);
    cout << "testPush2 pass\n";
}

void testPush3() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    //Build Dozer
    game.getPlayer(1)->buildUnit(0);
    game.getPlayer(2)->buildUnit(0);
    game.getPlayer(2)->buildUnit(1);
    pair<int,int> position1 = make_pair(2,2);
    pair<int,int> position2 = make_pair(2,3);
    pair<int,int> position3 = make_pair(2,4);
    pair<int,int> position4 = make_pair(2,5);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position3);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    vector<pair<int,int> > path;
    path.push_back(position2);
    path.push_back(position3);
    game.pushUnit(game.getPlayer(1)->getUnit(0), path, game.getPlayer(1)->getUnit(0));
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position2);
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 3);
    assert(game.getPlayer(2)->getUnit(0)->getPosition() == position3);
    assert(game.getPlayer(2)->getUnit(1)->getPosition() == position4);
    assert(game.getPlayer(2)->getUnit(0)->getLevel() == 1);
    assert(game.getPlayer(2)->getUnit(1)->getLevel() == 1);
    cout << "testPush3 pass\n";
}

void testPush4() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    //Build Dozer
    game.getPlayer(1)->buildUnit(0);
    game.getPlayer(2)->buildUnit(0);
    game.getPlayer(2)->buildUnit(1);
    pair<int,int> position1 = make_pair(2,0);
    pair<int,int> position2 = make_pair(2,1);
    pair<int,int> position3 = make_pair(2,2);
    pair<int,int> position4 = make_pair(2,3);
    pair<int,int> position5 = make_pair(2,4);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position3);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    vector<pair<int,int> > path;
    path.push_back(position2);
    path.push_back(position3);
    game.pushUnit(game.getPlayer(1)->getUnit(0), path, game.getPlayer(1)->getUnit(0));
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position3);
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 3);
    assert(game.getPlayer(2)->getUnit(0)->getPosition() == position4);
    assert(game.getPlayer(2)->getUnit(1)->getPosition() == position5);
    assert(game.getPlayer(2)->getUnit(0)->getLevel() == 2);
    assert(game.getPlayer(2)->getUnit(1)->getLevel() == 2);
    cout << "testPush4 pass\n";
}

void testPush5() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    //Build Dozer
    game.getPlayer(1)->buildUnit(0);
    game.getPlayer(2)->buildUnit(0);
    game.getPlayer(2)->buildUnit(1);
    pair<int,int> position1 = make_pair(2,0);
    pair<int,int> position2 = make_pair(2,1);
    pair<int,int> position3 = make_pair(2,2);
    pair<int,int> position4 = make_pair(2,3);
    pair<int,int> position5 = make_pair(2,4);
    game.addObstacle(position4);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position3);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    vector<pair<int,int> > path;
    path.push_back(position2);
    path.push_back(position3);
    game.pushUnit(game.getPlayer(1)->getUnit(0), path, game.getPlayer(1)->getUnit(0));
    assert(game.getPlayer(1)->getUnit(0)->getPosition() == position3);
    assert(game.getPlayer(1)->getUnit(0)->getLevel() == 3);
    assert(game.getPlayer(2)->getUnit(0)->getPosition() == position4);
    assert(game.getPlayer(2)->getUnit(1)->getPosition() == position5);
    assert(game.getPlayer(2)->getUnit(0)->getLevel() == 2);
    assert(game.getPlayer(2)->getUnit(1)->getLevel() == 2);
    cout << "testPush5 pass\n";
}

void testPushable1() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    game.getPlayer(2)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,0);
    pair<int,int> position2 = make_pair(2,1);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    assert(game.pushable(game.getUnitAtPosition(position1), position2) == true);
    cout << "testPushable1 pass\n";
}

void testPushable2() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    game.getPlayer(2)->buildUnit(0);
    pair<int,int> position1 = make_pair(2,0);
    pair<int,int> position2 = make_pair(2,-1);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position1);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    assert(game.pushable(game.getUnitAtPosition(position1), position2) == false);
    cout << "testPushable2 pass\n";
}

void testPushable3() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    game.getPlayer(2)->buildUnit(0);
    pair<int,int> position2 = make_pair(2,1);
    pair<int,int> position3 = make_pair(2,2);
    game.addObstacle(position3);
    game.getPlayer(2)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(2)->activateUnit(game.getPlayer(2)->getInactiveUnit(0));
    assert(game.pushable(game.getUnitAtPosition(position2), position3) == true);
    cout << "testPushable3 pass\n";
}

void testPushable4() {
    //Create game object
    Game game("Andy", "Auto", "Bob", "Aero", 9, 6);
    game.getPlayer(1)->buildUnit(0);
    pair<int,int> position2 = make_pair(2,1);
    pair<int,int> position3 = make_pair(2,2);
    game.addObstacle(position3);
    game.getPlayer(1)->getInactiveUnit(0)->setPosition(position2);
    game.getPlayer(1)->activateUnit(game.getPlayer(1)->getInactiveUnit(0));
    assert(game.pushable(game.getUnitAtPosition(position2), position3) == false);
    cout << "testPushable4 pass\n";
}

int main() {
    //testMoveUnit();
    //testDecon();

    //testAnyWithinRange1();
    //testAnyWithinRange2();

    //testPrintWithinRange1();
    //testPrintWithinRange2();
    //testPrintWithinRange3();

    //testDestroy1();
    //testDestroy2();

    testPush1();
    testPush2();
    testPush3();
    testPush4();
    testPush5();

    /*
    testPushable1();
    testPushable2();
    testPushable3();
    testPushable4();
    */
    return 0;
}
