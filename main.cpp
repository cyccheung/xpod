/*
Driver program for xpod game. Things to note:
Default position for units is -1,-1. 0,0 is the bottom left square
*/

#include "Game.h"
#include "Pod.h"
#include "Arena.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    //Get player's names and pods they want to play with
    string player1Name = "";
    string player2Name = "";
    string player1Pod = "";
    string player2Pod = "";
    //Get preferred arena size
    int rowIn = 0;
    int colIn = 0;
/*
    //Make sure that player 1's name is not an empty string
    while(player1Name == "") {
        std::cout << "Player 1 Name: ";
        std::cin >> player1Name;
    }
    //Make sure that player 1's pod choice is one of the 8 pods
    while(player1Pod != "Aero" && player1Pod != "Auto" && player1Pod != "Robo" && player1Pod != "Wild" && player1Pod != "Dragon" &&
        player1Pod != "Monster" && player1Pod != "Arachno" && player1Pod != "Aqua") {
            std::cout << "Player 1 Pod: ";
            std::cin >> player1Pod;
    }
    //Make sure that player 2's name is not an empty string or equal to player 1's name
    while(player2Name == "" || player2Name == player1Name) {
        std::cout << "Player 2 Name: ";
        std::cin >> player2Name;
    }
    //Make sure that player 2's pod name is one of the 8 pods
    while(player2Pod != "Aero" && player2Pod != "Auto" && player2Pod != "Robo" && player2Pod != "Wild" && player2Pod != "Dragon" &&
        player2Pod != "Monster" && player2Pod != "Arachno" && player2Pod != "Aqua") {
            std::cout << "Player 2 Pod: ";
            std::cin >> player2Pod;
    }


    //Make sure rows is at least 9
    while(rowIn < 9) {
        cout << "Arena Rows (At least 9): ";
        cin >> rowIn;
    }
    //Make sure columns is at least 6
    while(colIn < 6) {
        cout << "Arena Columns (At least 6): ";
        cin >> colIn;
    }
*/

    player1Name = "Andy";
    player2Name = "Bob";
    player1Pod = "Aero";
    player2Pod = "Monster";
    rowIn = 9;
    colIn = 6;

    //Create Game object
    Game game(player1Name, player1Pod, player2Name, player2Pod, rowIn, colIn);

    cout << "\nGame start:\n\n";

    //Get player's choices for starter kit
    game.printLine();
    cout << "Player 1:\n";
    game.starterKit(game.getPlayer(1));
    game.printLine();
    cout << "Player 2:\n";
    game.starterKit(game.getPlayer(2));

    //If no one has 3 points yet, keep playing
    while(game.playerWin() == 0) {
        game.printLine();
        //Print out scores
        cout << game.getPlayer(1)->getName() << ": " << game.getScore(1) << " points\n";
        cout << game.getPlayer(2)->getName() << ": " << game.getScore(2) << " points\n";
        //Print out player's turn
        cout << game.getActivePlayer()->getName() << "'s turn\n\n";
        //Print out player's active units and inactive units
        game.getActivePlayer()->printActive();
        cout << "\n";
        game.getActivePlayer()->printInactive();
        //Variable to store player input
        int actionChoice = -1;
        game.checkActionChoice(actionChoice);
        int choice = -1;
        game.printLine();
        switch(actionChoice) {
            case 1 : {
                //Print out plansheet
                game.getActivePlayer()->printPlanSheet();
                //Ask for index of unit to build
                game.checkBuildIndex(choice);
                //Build unit
                game.getActivePlayer()->buildUnit(choice);
                //End of turn
                game.changeTurn();
                break;
            }
            case 2 : {
                //Print out inactive units
                game.getActivePlayer()->printInactive();
                //Ask for index of unit to place
                game.checkPlaceIndex(choice);
                pair<int,int> placeChoice = make_pair(-1,-1);
                game.checkPlacePosition(placeChoice);
                //Place unit
                game.getActivePlayer()->getInactiveUnit(choice)->setPosition(placeChoice);
                game.getActivePlayer()->activateUnit(game.getActivePlayer()->getInactiveUnit(choice));
                //End of turn
                game.changeTurn();
                break;
            }
            case 3 : {
                //Print out active units
                game.getActivePlayer()->printActive();
                int unitChoice;
                game.checkActivateIndex(unitChoice);
                game.printLine();
                while(game.getActivePlayer()->getUnit(unitChoice)->ifFrozen()) {
                    cout << game.getActivePlayer()->getUnit(unitChoice)->getName() << " is frozen, choose another unit\n";
                    cin >> unitChoice;
                }
                //Print out unit's available actions
                game.printUnitActions(game.getActivePlayer()->getUnit(unitChoice));
                cout << "\n";
                //Enact actions
                //game.enactUnitActions(game.getActivePlayer()->getUnits().at(unitChoice));
                game.enactUnitActions(game.getActivePlayer()->getUnit(unitChoice));
                //Check if chosen unit has scare and if it does, scare adjacent enemies
                game.scareEnemies(game.getActivePlayer()->getUnit(unitChoice));
                //End of turn
                game.changeTurn();
                break;
            }
            case 4 : {
                //Print out active units
                game.getActivePlayer()->printActive();
                //Ask for index of unit to unfreeze
                cout << "Enter index of unit to unfreeze:";
                cin >> choice;
                //Unfreeze selected unit
                game.unfreezeUnit(game.getActivePlayer()->getUnit(choice));
                //End of turn
                game.changeTurn();
                break;
            }
            case 5 : {
                //Print plansheet
                game.getActivePlayer()->printPlanSheet();
                break;
                //Do not change turn
            }
            case 6 : {
                //Print out board
                game.printBoard();
                break;
                //Do not change turn
            }
        }
        cout << "\n";
        //Check for units in home row, increment score, and remove unit
        game.ifScored();
    }
    //Once there is a winner, announce winner
    cout << "The winner is Player " << game.playerWin();

    return 0;
}

void CheckPlayerInput() {
    cout << "Test\n";
}
