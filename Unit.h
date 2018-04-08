#ifndef UNIT_H
#define UNIT_H

/*
Each pod has a variety of units that the player can build. Units can have the
following abilities:
    Movement:
    Move, Jump, Fly, Push
    Special:
    Decon, Carry, Repair, Eat, Scare, Web
Each unit has the following private member variables:
A name (i.e AlphaBot)
Current levl
Maximum level
A vector of ints containing the part numbers unit is made up of
Vectors of ints containing the parts needed to go between levels
A vector of ints containing movement information in the following format:
Move, Jump, Fly, Push
(i.e) move 2 --> <2,0,0,0>
(i.e) fly 3 --> <0,0,3,0>

A vector of pair<int, int> containing ability mgnitudes, range in the following format:
Decon, Repair, Carry, Eat, Scare, Web <magnitudes,range>
(i.e) decon R2 --> <1,2>, <0,0>, <0,0>, <0,0>, <0,0>, <0,0>
(i.e) decon +1 --> <2,1>, <0,0>, <0,0>, <0,0>, <0,0>, <0,0>
(i.e) decon +1 and carry --> <2,1>, <0,0>, <1,0>, <0,0>, <0,0>, <0,0>
*/

#include <string>
#include "Piece.h"

class Unit {
public:
    //Prints out unit's level and abilities in the following format:
    //Ability (Magnitude if not 1)
    /* i.e
    AlphaBot Level 3:
    move 2, decon, repair

    ExtendoBot Level 2:
    move 1, decon R2
    */
    const void printInfo() const;

    //Returns unit's move ability
    const std::string getMove() const;

    //Returns unit's level
    const int getLevel();

    //Returns unit's max level
    const int getMaxLevel();

    //Returns pieces making up unit in a vector of ints
    const std::vector<int> getPieces() const = 0;

    //Returns unit's pieces needed to go from level x-1 to x
    const std::vector<int> getLevelPieces(int x) const = 0;

private:
    std::string name;           //Unit's name
    int level;                  //Current level
    int maxLevel;               //Maximum level possible
    bool frozen;                //Whether unit has been frozen or webbed
    std::vector<int> movement;  //
    std::vector<std::pair<int, int> > abilities;    //Described above
    std::vector<int> pieces;    //Pieces making up unit currently
    std::vector<int> pieces12;  //Pieces needed to go from level 1 to 2
    std::vector<int> pieces23;  //Pieces needed to go from level 2 to 3
    std::vector<int> pieces34;  //Pieces needed to go from level 3 to 4
};

#endif
