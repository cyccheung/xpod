#include "Game.h"
#include <cmath>

void Game::printBoard() {
    //const int rows = arena.getRows();
    //const int cols = arena.getColumns();
    //Create 2D array the size of arena
    //char arenaArray[rows][cols];
    //Create 2D vector the size of arena
    std::vector<char> arenaRow;
    for(int i = 0; i < arena.getColumns(); ++i) {
        arenaRow.push_back('o');
    }
    std::vector<std::vector<char> > arenaArray;
    //Fill in arena with empty squares
    for(int i = 0; i < arena.getRows(); ++i) {
        arenaArray.push_back(arenaRow);
    }

    //Fill in arena with home row
    for(int i = 0; i < arena.getColumns(); ++i) {
        arenaArray[0][i] = '-';
        arenaArray[arena.getRows() - 1][i] = '-';
    }

    char player2Index = 'A';
    //Fill in array with player units
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        //Fills in arena with unit indices starting at 1
        arenaArray.at(player1.getUnit(i)->getPosition().first).at(player1.getUnit(i)->getPosition().second) = (char)i + 1 + '0';
    }
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        //Fills in arena with unit indices starting at 'A'
        arenaArray[player2.getUnit(i)->getPosition().first][player2.getUnit(i)->getPosition().second] = player2Index;
        //Increments 'A' to 'B' and so on for every unit
        ++player2Index;
    }
    player2Index = 'A';
    //Fill in arena with obstacles
    for(int i = 0; i < (int)arena.getObstacles().size(); ++i) {
        arenaArray[arena.getObstacles().at(i).first][arena.getObstacles().at(i).second] = 'x';
    }



    //Print out arenaArray
    std::cout << "Player 1\n";
    //Print out list of player 1 active units on the arena with indices
    std::cout << "Active Units:\n";
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        std::cout << i + 1 << ": " << player1.getUnit(i)->getName() << "\n";
    }
    //Print out list of player 1 inactive units waiting to be placed
    std::cout << "Inactive Units:\n";
    for(int i = 0; i < (int)player1.getInactiveUnits().size(); ++i) {
        std::cout << player1.getInactiveUnit(i)->getName() << "\n";
    }

    std::cout << "\n";
    //Print out arena
    for(int i = 0; i < arena.getRows(); ++i) {
        std::cout << "\t\t";
        for(int j = 0; j < arena.getColumns(); ++j) {
            std::cout << arenaArray[i][j];
        }
        std::cout << "\n";
    }

    std::cout << "\nPlayer 2\n";
    //Print out list of player 2 active units on the arena with indices
    std::cout << "Active Units:\n";
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        std::cout << player2Index << ": " << player2.getUnit(i)->getName() << "\n";
        ++player2Index;
    }
    //Print out list of player 2 inactive units waiting to be placed
    std::cout << "Inactive Units:\n";
    for(int i = 0; i < (int)player2.getInactiveUnits().size(); ++i) {
        std::cout << player2.getInactiveUnit(i)->getName() << "\n";
    }
}

//Prints line to separate moves, makes it easier for player to see
void Game::printLine() {
    std::cout << "------------------------------------------------\n";
}

const std::pair<int,int> Game::getArenaSize() {
    return std::make_pair(arena.getRows(), arena.getColumns());
}

void Game::addObstacle(const std::pair<int,int> &position) {
    arena.addObstacle(position);
}

Player* Game::getPlayer(const int playerNumber) {
    if(playerNumber == 1) {
        return &player1;
    }
    return &player2;
}

void Game::starterKit(Player* playerPtr) {
    std::cout << "Starting Options:\n";
    int choice = 0;
    if(playerPtr->getPod()->getName() == "Aero") {
        std::cout << "Option 1:\n" << "Copter Raider, Jump Jet, Rescue Jet\n";
        std::cout << "Option 2:\n" << "MiniCopter, Jet Raider, Rescue Jet\n";
        std::cout << "Option 3:\n" << "Jet Raider, Glider Medic, Interceptor\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(3);
            playerPtr->buildUnit(15);
            playerPtr->buildUnit(19);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(16);
            playerPtr->buildUnit(15);
            playerPtr->buildUnit(19);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(6);
            playerPtr->buildUnit(11);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Auto") {
        std::cout << "Option 1:\n" << "Speedster, Forklift, Basher\n";
        std::cout << "Option 2:\n" << "Spike, Pushabout, ArmoredSled\n";
        std::cout << "Option 3:\n" << "Rollabout, Rollabout, Basher\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(20);
            playerPtr->buildUnit(9);
            playerPtr->buildUnit(2);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(21);
            playerPtr->buildUnit(16);
            playerPtr->buildUnit(1);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(18);
            playerPtr->buildUnit(18);
            playerPtr->buildUnit(2);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Robo") {
        std::cout << "Option 1:\n" << "AlphaBot, ExtendoBot, Fixit\n";
        std::cout << "Option 2:\n" << "JumpBot, ExtendoBot, Patroller\n";
        std::cout << "Option 3:\n" << "BrainBot, Patroller, Sparks\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(0);
            playerPtr->buildUnit(6);
            playerPtr->buildUnit(7);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(10);
            playerPtr->buildUnit(6);
            playerPtr->buildUnit(18);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(2);
            playerPtr->buildUnit(18);
            playerPtr->buildUnit(21);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Wild") {
        std::cout << "Option 1:\n" << "Gorilla, Moth, Stinging Ant\n";
        std::cout << "Option 2:\n" << "King Crab, Moth, Mantis\n";
        std::cout << "Option 3:\n" << "Rattler, Rattler, Mantis\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(8);
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(19);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(10);
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(12);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(16);
            playerPtr->buildUnit(16);
            playerPtr->buildUnit(12);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Dragon") {
        std::cout << "Option 1:\n" << "Land Dragon, Cave Beetle, Young Hatchling\n";
        std::cout << "Option 2:\n" << "Storm Dragon, Cave Beetle, Dragon Slug\n";
        std::cout << "Option 3:\n" << "Land Dragon, Crawling, Young Hatchling\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(9);
            playerPtr->buildUnit(0);
            playerPtr->buildUnit(15);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(12);
            playerPtr->buildUnit(0);
            playerPtr->buildUnit(5);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(9);
            playerPtr->buildUnit(1);
            playerPtr->buildUnit(15);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Monster") {
        std::cout << "Option 1:\n" << "Frightful, Dizzy, Gremlin\n";
        std::cout << "Option 2:\n" << "Slither, It, Creepy Crawler\n";
        std::cout << "Option 3:\n" << "It, Bucky, Gremlin\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(7);
            playerPtr->buildUnit(3);
            playerPtr->buildUnit(8);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(19);
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(2);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(1);
            playerPtr->buildUnit(8);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Arachno") {
        std::cout << "Option 1:\n" << "Wolf Spider, Venomous Nettler, Tickler\n";
        std::cout << "Option 2:\n" << "Uncle Longlegs, Venomous Nettler, Bugling\n";
        std::cout << "Option 3:\n" << "Web Flinger, Cricket, Bugling\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(16);
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(12);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(13);
            playerPtr->buildUnit(14);
            playerPtr->buildUnit(2);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(15);
            playerPtr->buildUnit(3);
            playerPtr->buildUnit(2);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
    else if(playerPtr->getPod()->getName() == "Aqua") {
        std::cout << "Option 1:\n" << "Hammerhead, Piranha, Shrimp\n";
        std::cout << "Option 2:\n" << "Sea Tortoise, Man-o-War, Shrimp\n";
        std::cout << "Option 3:\n" << "Stingray, Piranha, Flying Fish\n";
        checkStarterKit(choice);
        if(choice == 1) {
            playerPtr->buildUnit(5);
            playerPtr->buildUnit(9);
            playerPtr->buildUnit(16);
        }
        else if(choice == 2) {
            playerPtr->buildUnit(18);
            playerPtr->buildUnit(8);
            playerPtr->buildUnit(16);
        }
        else if(choice == 3) {
            playerPtr->buildUnit(17);
            playerPtr->buildUnit(9);
            playerPtr->buildUnit(2);
        }
        //Assume player will enter valid choice every time, will never have to come here
        else {
            std::cout << "Invalid Choice\n";
        }
    }
}

void Game::printUnitActions(Unit* unitPtr) {
    //Prints unit's abilities
    unitPtr->printInfo();
    std::cout << "\n";
    //Print board
    printBoard();
}

void Game::unitSpecialActions(Unit* unitPtr) {
    std::cout << "Choose an ability to use:\n";
    for(int i = 0; i < (int)unitPtr->getAbilities().size(); ++i) {
        if(unitPtr->getAbilities().at(i)) {
            if(i == 0) {    //Repair
                if(anyWithinRange(unitPtr, 1)) {
                    std::cout << "[0]: Repair\n";
                }
            }
            else if(i == 1) {   //Carry
                if(anyWithinRange(unitPtr, 1)) {
                    std::cout << "[1]: Carry\n";
                }
            }
            else if(i == 2) {   //Eat
                if(anyWithinRange(unitPtr, 1, 1)) {
                    std::cout << "[2]: Eat\n";
                }
            }
            else if(i == 3) {   //Web
                if(anyWithinRange(unitPtr, 2)) {
                    std::cout << "[3]: Web\n";
                }
            }
        }
    }
    //Print out decon choice
    if(unitPtr->ifDecon()) {
        std::cout << "[4]: Decon\n";
    }
    std::cout << "[5]: Nothing\n";
    int actionChoice;
    std::cin >> actionChoice;
    std::pair<int,int> positionChoice = std::make_pair(0,0);
    if(actionChoice == 0) {   //Repair
        std::cout << "Enter the position of the unit to repair:\n";
        printUnitsInRange(unitPtr, 1);
        std::cin >> positionChoice.first >> positionChoice.second;
        repairUnit(getUnitAtPosition(positionChoice), getUnitPlayer(getUnitAtPosition(positionChoice)));
    }
    else if(actionChoice == 1) {  //Carry
        std::cout << "Enter the position of the unit to carry:\n";
        printUnitsInRange(unitPtr, 1);
        std::cin >> positionChoice.first >> positionChoice.second;
        //TODO: Ask where to put down carried unit after moving

    }
    else if(actionChoice == 2) {  //Eat
        std::cout << "Enter the position of the unit to eat:\n";
        printUnitsEat(unitPtr);
        std::cin >> positionChoice.first >> positionChoice.second;
        //Deconstructs unit
        deconUnit(getUnitAtPosition(positionChoice), getUnitPlayer(getUnitAtPosition(positionChoice)));
        //Repairs eating unit if eating unit is not max level
        if(unitPtr->getLevel() != unitPtr->getMaxLevel()) {
            repairUnit(unitPtr, getUnitPlayer(unitPtr));
        }
        else {
            std::cout << unitPtr->getName() << " is already at max level and was not repaired\n";
        }
    }
    else if(actionChoice == 3) {  //Web
        std::cout << "Enter the position of the unit to web:\n";
        printUnitsInRange(unitPtr, 2);
        std::cin >> positionChoice.first >> positionChoice.second;
        freezeUnit(getUnitAtPosition(positionChoice));
    }
    else if(actionChoice == 4) {  //Decon
        printUnitsInRange(unitPtr, unitPtr->getDeconVect().second);
        std::cout << "Enter the position of the unit to decon:\n";
        std::cin >> positionChoice.first >> positionChoice.second;
        deconUnit(getUnitAtPosition(positionChoice), getUnitPlayer(getUnitAtPosition(positionChoice)));
    }
}

void Game::unitMovementActions(Unit* unitPtr) {
    std::cout << "Move " << unitPtr->getName() << " by typing in path (2 3 2 4 to move to 2,4 through 2,3)\n";
    //TODO: Proper check if input is correct and if not, prompt again
    //Get player's selected path
    std::pair<int,int> tempPosition = std::make_pair(0,0);
    std::vector<std::pair<int,int> > path;
    //int counter = 0;
    for(int i = 0; i < (int)unitPtr->getMoveMagnitude(); ++i) {
        std::cin >> tempPosition.first >> tempPosition.second;
        path.push_back(tempPosition);
    }
    //while(std::cin >> tempPosition.first && std::cin >> tempPosition.second && counter < unit.getMoveMagnitude()) {
        //path.push_back(tempPosition);
        //++counter;
    //}
    if(unitPtr->moreMove()) {
        std::cout << unitPtr->getName() << " has more than one movement ability, choose one to use\n";
        for(int i = 0; i < (int)unitPtr->getMovement().size(); ++i) {
            if(unitPtr->getMovement().at(i) != 0) {
                std::cout << "[" << i << "]: ";
                if(i == 0) {
                    std::cout << "move ";
                }
                else if(i == 1) {
                    std::cout << "jump ";
                }
                else if(i == 2) {
                    std::cout << "fly ";
                }
                else if(i == 3) {
                    std::cout << "push ";
                }
                std::cout << unitPtr->getMovement().at(i) << "\n";
            }
        }
        int moveChoice;
        std::cin >> moveChoice;
        if(moveChoice == 3) {
            pushUnit(unitPtr, path, unitPtr);
        }
        else {
            moveUnit(unitPtr, path);
        }
    }
    else if(unitPtr->getMovement().at(3) != 0) {
        pushUnit(unitPtr, path, unitPtr);
    }
    else {
        moveUnit(unitPtr, path);
    }
    std::cout << unitPtr->getName() << " has moved to " << unitPtr->getPosition().first << ", " << unitPtr->getPosition().second << "\n";
}

void Game::enactUnitActions(Unit* unitPtr) {
    std::cout << "\n[0]: Move\n[1]: Special\n";
    int unitChoice;
    std::cin >> unitChoice;
    if(unitChoice) {
        unitSpecialActions(unitPtr);
        unitMovementActions(unitPtr);
    }
    else if(!unitChoice) {
        unitMovementActions(unitPtr);
        unitSpecialActions(unitPtr);
    }
}

void Game::moveUnit(Unit* unitPtr, const std::vector<std::pair<int,int> > &path) {
    unitPtr->setPosition(path.at(path.size() - 1));
}

void Game::pushUnit(Unit* unitPtr, std::vector<std::pair<int,int> > path, Unit* pusher) {
    //Push step by step
    for(int i = 0; i < (int)path.size(); ++i) {
        //Variables to remember which direction path heads in
        int rowDiff = path.at(i).first - unitPtr->getPosition().first;
        int colDiff = path.at(i).second - unitPtr->getPosition().second;
        //Calculate position where a pushed unit would go if one exists
        std::pair<int,int> pushedUnitPosition = std::make_pair(path.at(i).first + rowDiff, path.at(i).second + colDiff);
        //If destination is invalid, do nothing. For unit at end of row
        if(!unitOnSquare(path.at(i)) && !validSquare(unitPtr, path.at(i))) {}
        //If there are no units in the way, move as per normal
        else if(!unitOnSquare(path.at(i))) {
            //std::cout << "First case: " << unitPtr->getName() << "\n";
            unitPtr->setPosition(path.at(i));
        }
        //If there is a unit in the way
        else if(unitOnSquare(path.at(i))) {
            //Find position of unit at the end of push
            std::pair<int,int> lastUnitPosition = std::make_pair(path.at(i).first, path.at(i).second);
            std::pair<int,int> lastUnitDestination = std::make_pair(lastUnitPosition.first + rowDiff, lastUnitPosition.second + colDiff);
            //Loop through all the units in the row to find the position of the unit at the end of the row being pushed
            //Note: First condition checks if there is a unit at the next position and second condition checks if there is an obstacle in the way of a non flying unit. If there is an obstacle with a flying unit on it and a non flying unit next to it, the flying unit will not be affected by the push
            //std::cout << "1\n";
            //See if the row of units is movable
            bool movable = true;
            while(unitOnSquare(lastUnitPosition)) {
                //std::cout << "2\n";
                if(pushable(getUnitAtPosition(lastUnitPosition), lastUnitDestination)) {
                    //Increment positions to next position
                    lastUnitPosition.first += rowDiff;
                    lastUnitPosition.second += colDiff;
                    lastUnitDestination.first += rowDiff;
                    lastUnitDestination.second += colDiff;
                    //std::cout << "3\n";
                }
                else {
                    movable = false;
                    break;
                }
            }
            lastUnitPosition.first -= rowDiff;
            lastUnitPosition.second -= colDiff;
            lastUnitDestination.first -= rowDiff;
            lastUnitDestination.second -= colDiff;


            //If last unit cannot be pushed further
            //if(!pushable(getUnitAtPosition(lastUnitPosition), lastUnitDestination)) {
                //std::cout << "Here\n";
            //}
            //If row is movable, move entire row
            if(movable) {
                //std::cout << "Second case: " << unitPtr->getName() << "\n";
                //Create vector to pass into push of pushed unit
                std::vector<std::pair<int,int> > tempPath;
                tempPath.push_back(pushedUnitPosition);
                //Call push on unit being pushed, and keep the same pusher parameter
                pushUnit(getUnitAtPosition(path.at(i)), tempPath, pusher);
                //Move pushing unit
                unitPtr->setPosition(path.at(i));
            }
            //If row is not movable, decon everything in row except pusher
            else {
                //std::cout << "Third case: " << unitPtr->getName() << "\n";
                //Deconstruct unit in the way
                deconUnit(getUnitAtPosition(path.at(i)), getUnitPlayer(getUnitAtPosition(path.at(i))));
                //Create vector to pass into push of pushed unit
                std::vector<std::pair<int,int> > tempPath;
                tempPath.push_back(pushedUnitPosition);
                //Call push on unit being pushed to deconstruct recursively
                pushUnit(getUnitAtPosition(path.at(i)), tempPath, pusher);
                /*
                //Deconstruct this unit if this unit is not the original pusher
                if(unitPtr != pusher) {
                    deconUnit(unitPtr, getUnitPlayer(unitPtr));
                }
                */
                //Do not move any of the units
            }
        }
        /*
        //If there is a unit in the way and nothing beyond, recursively call push on unit being pushed
        else if(unitOnSquare(path.at(i)) && !arena.edgeOfMap(pushedUnitPosition) && arena.openSquare(pushedUnitPosition)) {

        }
        //If there is a unit in the way and the edge of the map or an obstacle in the way
        else if(unitOnSquare(path.at(i)) && (arena.edgeOfMap(pushedUnitPosition) || !arena.openSquare(pushedUnitPosition))) {

        }
        */
    }
}

void Game::deconUnit(Unit* unitPtr, Player* playerPtr) {
    //If unit will be destroyed, call removeUnit
    if(unitPtr->getLevel() == 1) {
        std::cout << unitPtr->getName() << " is destroyed\n";
        playerPtr->removeUnit(unitPtr);
    }
    //Otherwise deconstruct as per normal
    else {
        //Returns one level's worth of bricks
        playerPtr->returnBricks(unitPtr);
        //Lowers unit's level and changes abilities
        unitPtr->getDecon();
        std::cout << unitPtr->getName() << " is deconstructed to level " << unitPtr->getLevel() << "\n";
    }
}

void Game::repairUnit(Unit* unitPtr, Player* playerPtr) {
    //Uses one level's worth of bricks
    playerPtr->useBricks(unitPtr, 1);
    //Repairs unit
    unitPtr->getRepair();
    std::cout << unitPtr->getName() << " is repaired to level " << unitPtr->getLevel() << "\n";
}

void Game::freezeUnit(Unit* unitPtr) {
    unitPtr->freeze();
    std::cout << unitPtr->getName() << " is frozen\n";
}

void Game::unfreezeUnit(Unit* unitPtr) {
    unitPtr->unfreeze();
    std::cout << unitPtr->getName() << " is unfrozen\n";
}

const bool Game::unitOnSquare(const std::pair<int,int> &position) {
    //If there is a Player 1 unit
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        if(player1.getUnit(i)->getPosition() == position) {
            return true;
        }
    }
    //If there is a Player 2 unit
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        if(player2.getUnit(i)->getPosition() == position) {
            return true;
        }
    }
    return false;
}

const bool Game::player1UnitOnSquare(const std::pair<int,int> &position) {
    //If there is a Player 1 unit
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        if(player1.getUnit(i)->getPosition() == position) {
            return true;
        }
    }
    return false;
}

const bool Game::player2UnitOnSquare(const std::pair<int,int> &position) {
    //If there is a Player 2 unit
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        if(player2.getUnit(i)->getPosition() == position) {
            return true;
        }
    }
    return false;
}

const bool Game::emptySquare(const std::pair<int,int> &position) {
    //If there is an obstacle
    if(!arena.openSquare(position)) {
        return false;
    }
    //Or if there is a unit
    else if(unitOnSquare(position)) {
        return false;
    }
    //If everything passed, return true
    return true;
}

const bool Game::validSquare(Unit* unitPtr, const std::pair<int,int> &position) {
    //Cannot be outside arena
    if(!arena.inArena(position)) {
        return false;
    }
    //If unit flies
    if(unitPtr->getMovement().at(2) != 0) {
        //Cannot land on other units
        if(unitOnSquare(position)) {
            return false;
        }
        else {
            return true;
        }
    }
    //Otherwise units cannot step on other units or obstacles
    else {
        if(emptySquare(position)) {
            return true;
        }
        else {
            return false;
        }
    }
    //Return false by default
    return false;
}

const bool Game::validPath(Unit* unitPtr, const std::vector<std::pair<int,int> > &path) {
    //Units with move
    if(unitPtr->getMove().at(0) != 0) {
        //Restriction: Cannot move through obstacles or other units
        for(int i = 0; i < (int)path.size(); ++i) {
            if(!emptySquare(path.at(i))) {
                return false;
            }
        }
    }
    //Units with jump
    else if(unitPtr->getMove().at(1) != 0) {
        //Restriction: Cannot land on obstacles or other units
        //If final square is not a valid square
        if(!emptySquare(path.at(path.size() - 1))) {
            return false;
        }
    }
    //Units with fly
    else if(unitPtr->getMove().at(2) != 0) {
        //Restriction: Cannot land on another unit
        std::pair<int,int> position = path.at(path.size() - 1);
        if(unitOnSquare(position)) {
            return false;
        }
    }
    //Units with push
    else if(unitPtr->getMove().at(3) != 0) {
        //Restriction: Cannot move through obstacles
        for(int i = 0; i < (int)path.size(); ++i) {
            if(!arena.openSquare(path.at(i))) {
                return false;
            }
        }
    }
    //If nothing returned false, return true
    return true;
}

const bool Game::pushable(Unit* unitPtr, const std::pair<int,int> &position) {
    //std::cout << "4\n";
    //If unit flies
    if(unitPtr->getMovement().at(2) != 0) {
        //Can be pushed anywhere on the arena
        if(arena.inArena(position)) {
            return true;
        }
    }
    //If unit does not fly
    else {
        //Can be pushed onto empty square on arena
        if(arena.openSquare(position) && arena.inArena(position)) {
            return true;
        }
    }
    return false;
}

Unit* Game::getUnitAtPosition(std::pair<int,int> position) {
    //Search for unit in player 1's units vector
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        if(player1.getUnit(i)->getPosition() == position) {
            return player1.getUnit(i);
        }
    }
    //Search for unit in player 2's units vector
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        if(player2.getUnit(i)->getPosition() == position) {
            return player2.getUnit(i);
        }
    }
    //If not found, print error message and return default unit to please compiler
    std::cout << "Error: Unit not found. Returned default unit.\n";
    //TODO: Returns player 1's first unit but find a better solution
    //return player1.getUnit(0);
    return nullptr;
    //return player1.getPod().getPlanSheet().at(0);
}

void Game::printUnitsInRange(Unit* unitPtr, const int range) {
    std::cout << player1.getName() << "'s units:\n";
    //Loop through all columns (if unit has move 2 and in column 4, check columns 2-6)
    for(int i = unitPtr->getPosition().second - range; i <= unitPtr->getPosition().second + range; ++i) {
        //Number of rows is whatever movement unit has remaining after moving columns
        //range - abs(unit.getPosition.second - i)) is the amount of movement the unit
        //still has after travelling to column i
        for(int j = unitPtr->getPosition().first - (range - abs(unitPtr->getPosition().second - i)); j <= unitPtr->getPosition().first + (range - abs(unitPtr->getPosition().second - i)); ++j) {
            //std::cout << "2\n";
            //Check that position is in the arena
            if((i < arena.getColumns() || i >= 0) && ((j < arena.getRows() || j >= 0))) {
                std::pair<int,int> tempPosition = std::make_pair(i,j);
                if(player1UnitOnSquare(tempPosition) && (getUnitAtPosition(tempPosition) != unitPtr)) {
                    std::cout << getUnitAtPosition(tempPosition)->getName() << " (" << getUnitAtPosition(tempPosition)->getPosition().first << ", " << getUnitAtPosition(tempPosition)->getPosition().second << ")\n";
                }
            }
        }
    }
    std::cout << player2.getName() << "'s units:\n";
    for(int i = unitPtr->getPosition().second - range; i <= unitPtr->getPosition().second + range; ++i) {
        //Number of rows is whatever movement unit has remaining after moving columns
        //range - abs(unit.getPosition.second - i)) is the amount of movement the unit
        //still has after travelling to column i
        for(int j = unitPtr->getPosition().first - (range - abs(unitPtr->getPosition().second - i)); j <= unitPtr->getPosition().first + (range - abs(unitPtr->getPosition().second - i)); ++j) {
            //Check that position is in the arena
            if((i < arena.getColumns() || i >= 0) && ((j < arena.getRows() || j >= 0))) {
                std::pair<int,int> tempPosition = std::make_pair(i,j);
                if(player2UnitOnSquare(tempPosition) && (getUnitAtPosition(tempPosition) != unitPtr)) {
                    std::cout << getUnitAtPosition(tempPosition)->getName() << " (" << getUnitAtPosition(tempPosition)->getPosition().first << ", " << getUnitAtPosition(tempPosition)->getPosition().second << ")\n";
                }
            }
        }
    }
}

void Game::printUnitsEat(Unit* unitPtr) {
    std::cout << player1.getName() << "'s units:\n";
    int range = unitPtr->getMoveMagnitude();
    //Loop through all columns (if unit has move 2 and in column 4, check columns 2-6)
    for(int i = unitPtr->getPosition().second - range; i < unitPtr->getPosition().second + range; ++i) {
        //Number of rows is whatever movement unit has remaining after moving columns
        //range - abs(unit.getPosition.second - i)) is the amount of movement the unit
        //still has after travelling to column i
        for(int j = unitPtr->getPosition().first - (range - abs(unitPtr->getPosition().second - i)); unitPtr->getPosition().first + (range - abs(unitPtr->getPosition().second - i)); ++j) {
            std::pair<int,int> tempPosition = std::make_pair(i,j);
            if(player1UnitOnSquare(tempPosition) && (getUnitAtPosition(tempPosition) != unitPtr)) {
                if(getUnitAtPosition(tempPosition)->getLevel() == 1) {
                    std::cout << getUnitAtPosition(tempPosition)->getName() << " (" << getUnitAtPosition(tempPosition)->getPosition().first << ", " << getUnitAtPosition(tempPosition)->getPosition().second << ")\n";
                }
            }
        }
    }
    std::cout << player2.getName() << "'s units:\n";
    for(int i = unitPtr->getPosition().second - range; i < unitPtr->getPosition().second + range; ++i) {
        //Number of rows is whatever movement unit has remaining after moving columns
        //range - abs(unit.getPosition.second - i)) is the amount of movement the unit
        //still has after travelling to column i
        for(int j = unitPtr->getPosition().first - (range - abs(unitPtr->getPosition().second - i)); unitPtr->getPosition().first + (range - abs(unitPtr->getPosition().second - i)); ++j) {
            std::pair<int,int> tempPosition = std::make_pair(i,j);
            if(player2UnitOnSquare(tempPosition) && (getUnitAtPosition(tempPosition) != unitPtr)) {
                if(getUnitAtPosition(tempPosition)->getLevel() == 1) {
                    std::cout << getUnitAtPosition(tempPosition)->getName() << " (" << getUnitAtPosition(tempPosition)->getPosition().first << ", " << getUnitAtPosition(tempPosition)->getPosition().second << ")\n";
                }
            }
        }
    }
}

const bool Game::ifWithinRange(Unit* unitPtr1, Unit* unitPtr2, const int range) {
    //If comparing the same unit, return false
    if(unitPtr1 == unitPtr2) {
        return false;
    }
    //Distance between 2,2 and 3,3 is abs(2-3) + abs(2-3) = 2
    int totalDifference = abs(unitPtr1->getPosition().first - unitPtr2->getPosition().first) + abs(unitPtr1->getPosition().second - unitPtr2->getPosition().second);
    if(totalDifference > range) {
        return false;
    }
    return true;
}

const bool Game::anyWithinRange(Unit* unitPtr, const int range) {
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        if(ifWithinRange(player1.getUnit(i), unitPtr, range)) {
            return true;
        }
    }
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        if(ifWithinRange(player2.getUnit(i), unitPtr, range)) {
            return true;
        }
    }
    return false;
}

const bool Game::anyWithinRange(Unit* unitPtr, const int range, const int level) {
    for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
        if(ifWithinRange(player1.getUnit(i), unitPtr, range) && player1.getUnit(i)->getLevel() == level) {
            return true;
        }
    }
    for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
        if(ifWithinRange(player2.getUnit(i), unitPtr, range) && player1.getUnit(i)->getLevel() == level) {
            return true;
        }
    }
    return false;
}

void Game::changeTurn() {
    if(activePlayer->getName() == player1.getName()) {
        activePlayer = &player2;
    }
    else if(activePlayer->getName() == player2.getName()) {
        activePlayer = &player1;
    }
    //playerTurn = !playerTurn;
}

Player* Game::getActivePlayer() {
    return activePlayer;
}

Player* Game::getUnitPlayer(Unit* unitPtr) {
    if(player1UnitOnSquare(unitPtr->getPosition())) {
        return &player1;
    }
    //If not player 1's unit, must be player 2's
    return &player2;
}

void Game::ifScored() {
    //Look at active player's units first
    if(activePlayer == &player1) {
        for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
            //If Player 1's unit is in Player 2's home row
            if(arena.ifHome(player1.getUnit(i)->getPosition(), true)) {
                ++player1Score;
                discardAfterScore(player1.getUnit(i));
            }
        }
        for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
            //If Player 1's unit is in Player 2's home row
            if(arena.ifHome(player2.getUnit(i)->getPosition(), false)) {
                ++player2Score;
                discardAfterScore(player2.getUnit(i));
            }
        }
    }
    else {
        for(int i = 0; i < (int)player2.getUnits().size(); ++i) {
            //If Player 1's unit is in Player 2's home row
            if(arena.ifHome(player2.getUnit(i)->getPosition(), false)) {
                ++player2Score;
                discardAfterScore(player2.getUnit(i));
            }
        }
        for(int i = 0; i < (int)player1.getUnits().size(); ++i) {
            //If Player 1's unit is in Player 2's home row
            if(arena.ifHome(player1.getUnit(i)->getPosition(), true)) {
                ++player1Score;
                discardAfterScore(player1.getUnit(i));
            }
        }
    }
}

void Game::discardAfterScore(Unit* unitPtr) {
    int choice = 0;
    //Print out bricks
    for(int i = 0; i < unitPtr->getLevelBricks(unitPtr->getLevel()); ++i) {
        std::cout << unitPtr->getBricks().at(i) << " ";
    }
    std::cout << "\nEnter index of brick (1-76) to discard:\n";
    //Get player's choice of brick to discard
    std::cin >> choice;
    if(player1UnitOnSquare(unitPtr->getPosition())) {
        //Remove unit from arena and all its bricks back into pod
        player1.removeUnit(unitPtr);
        //Remove chosen brick from pod
        player1.getPod()->removeBrick(choice);
    }
    else {
        //Remove unit from arena and all its bricks back into pod
        player2.removeUnit(unitPtr);
        //Remove chosen brick from pod
        player2.getPod()->removeBrick(choice);
    }
    std::cout << "Brick " << choice << " was discarded.\n";
}

const int Game::playerWin() const {
    if(player1Score >= 3) {
        return 1;
    }
    else if(player2Score >= 3) {
        return 2;
    }
    return 0;
}

const int Game::getScore(const int playerIndex) const {
    if(playerIndex == 1) {
        return player1Score;
    }
    else if(playerIndex == 2) {
        return player2Score;
    }
    return -1;
}

//-----------------Player input checks----------------------
void Game::checkStarterKit(int &choice) {
    while(choice != 1 && choice != 2 && choice != 3) {
        std::cout << "Choice: ";
        std::cin >> choice;
    }
}
