#ifndef GAME_H
#define GAME_H

/*
Overall management of the game.
Game object contains the following:
A pair of players

*/

#include "Unit.h"
#include "Pod.h"
#include "Arena.h"
#include <vector>
#include <string>

class Game {
public:

private:
    std::pair<Player, Player> players;      //Pair of players
};

#endif
