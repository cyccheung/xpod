#ifndef GAME_H
#define GAME_H

/*
Overall management of the game.
Game object contains the following:
A pair of players
Player's scores
Which player's turn it is
An arena (board)
*/

#include "Unit.h"
#include "Pod.h"
#include "Arena.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>

class Game {
public:
    //Game default constructor creates a game with an Aero player and an Auto player
    //Creates default 9x6 board
    Game()
        : player1(Player("A", "Aero")), player2(Player("B", "Auto")), player1Score(0), player2Score(0) {
            Arena board;
            arena = board;
        }
    //Game constructor creates a game with specified players
    Game(const std::string &player1In, const std::string &pod1In, const std::string &player2In, const std::string &pod2In, const int rowIn, const int colIn)
        : player1(Player(player1In, pod1In)), player2(Player(player2In, pod2In)), player1Score(0), player2Score(0) {
            Arena board(rowIn, colIn);
            arena = board;
            //Player 1 starts
            activePlayer = &player1;
        }

    //Function to display board with units
    void printBoard();

    //Function to return player member variables
    Player* getPlayer(const int playerNumber);

    //Function to print out starter kits, get player's choice, build appropriate units
    void starterKit(Player &player);

    //Function to get player's unit choice for turn
    //void selectUnit();

    //Function to print out selected unit's available movement and action choices
    void printUnitActions(Unit* unitPtr);

    //Function to get player's choice for special action
    void unitSpecialActions(Unit* unitPtr);

    //Function to get player's choice for movement action
    void unitMovementActions(Unit* unitPtr);

    //Gets and acts out player's requested actions
    void enactUnitActions(Unit* unitPtr);

    //Movement for units with move
    void moveUnit(Unit* unitPtr, const std::vector<std::pair<int,int> > &path);
    /*
    //Movement for units with jump
    void jumpUnit(Unit &unit);

    //Movement for units with fly
    void flyUnit(Unit &unit);
    */
    //Movement for units with push. Recursively pushes any units in the way
    //pusher parameter saves the original pusher so it does not get deconstructed
    void pushUnit(Unit* unitPtr, std::vector<std::pair<int,int> > path, Unit* pusher);

    //Deconstruct input unit once and return bricks to input player's pod
    void deconUnit(Unit* unitPtr, Player* playerPtr);

    //Repair input unit once and use bricks from input player's pod, assumes enough bricks
    void repairUnit(Unit* unitPtr, Player* playerPtr);

    //Freezes input unit
    void freezeUnit(Unit* unitPtr);

    //Unfreezes input unit
    void unfreezeUnit(Unit* unitPtr);

    //Returns if position square has a unit or obstacle on it
    const bool emptySquare(const std::pair<int,int> &position) const;

    //Returns if position square has a unit on it
    const bool unitOnSquare(const std::pair<int,int> &position) const;

    //Returns if position square has a player 1 unit on it
    const bool player1UnitOnSquare(const std::pair<int,int> &position) const;

    //Returns if position square has a player 2 unit on it
    const bool player2UnitOnSquare(const std::pair<int,int> &position) const;

    //Returns if position square is a valid square for given unit
    const bool validSquare(Unit* unitPtr, const std::pair<int,int> &position);

    //Returns if path is a valid path for unit to move along
    const bool validPath(Unit* unitPtr, const std::vector<std::pair<int,int> > &path) const;

    //Returns pointer to unit at a position by reference
    Unit* getUnitAtPosition(std::pair<int,int> position);

    //Prints out list of all units and their positions within a certain range of unit
    void printUnitsInRange(Unit* unitPtr, const int range);

    //Prints out list of adjacent level 1 units and their positions
    void printUnitsEat(Unit* unitPtr);

    //Returns if unit1 is within a certain range of unit2
    const bool ifWithinRange(Unit* unitPtr1, Unit* unitPtr2, const int range);

    //Returns if there are any units within a certain range of unit
    const bool anyWithinRange(Unit* unitPtr, const int range);

    //Overloads anyWithinRange for eat
    const bool anyWithinRange(Unit* unitPtr, const int range, const int level);

    //Function to end a turn
    void changeTurn();

    //Returns activePlayer pointer
    Player* getActivePlayer();

    //Returns pointer to player who owns input unit
    Player* getUnitPlayer(Unit* unitPtr);

    //Function to determine if any units have scored and if so, set the score accordingly
    //Calls discardAfterScore to remove scoring unit from arena
    void ifScored();

    //Function to let player choose brick to discard after scoring
    void discardAfterScore(Unit* unitPtr);

    //Function to determine if a player has won (3 points or more)
    //Returns 0 if nobody has won yet, 1 if player 1 wins, 2 if player 2 wins
    const int playerWin() const;

private:
    Player player1;
    Player player2;
    Player* activePlayer;   //Pointer at either player1 or player2 member variables
    int player1Score;
    int player2Score;
    //bool playerTurn;    //True if player 1's turn, false if player 2's turn
    Arena arena;
};

#endif
