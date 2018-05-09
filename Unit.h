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
Current level
Maximum level
An ordered vector of ints containing the part numbers max level unit is made up of, order
of vector follows plan sheets
Vectors of ints containing the number of parts needed to go between levels use these
numbers to traverse bricks vector
A vector of ints containing movement information in the following format:
Move, Jump, Fly, Push
(i.e) move 2 --> <2,0,0,0>
(i.e) fly 3 --> <0,0,3,0>

A vector of bools containing abilities in the following format:
Repair, Carry, Eat, Scare, Web
(i.e) Repair --> <1,0,0,0,0>
(i.e) Repair, Eat --> <1,0,1,0,0>
Only decon has a magnitude or range modifier (+1, R2...) so decon abilities are stored
as a separate member variable, a pair.

Note: Carry function is implemented in the game itself as it is easier to couple two
units together in game.cpp.

Declarations and implementations for all the units are here as well
This code is partitioned into the different pods in the
following order:
Aero, Auto, Robo, Wild, Dragon, Monster, Arachno, Aqua

Example constructor for unit
class Aircab : public Unit {
public:
    //Constructor creates unit of highest level
    Aircab()
        : Unit("Aircab", 2, 2, 2, 2, 0, 0) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,7,4,15};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        --level;
        if(level == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        ++level;
        if(level == 2) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }

private:
};

*/

#include <string>
#include <vector>

class Unit {
public:
    //Constructor for Unit
    Unit(std::string nameIn, int levelIn, int maxLevelIn, int bricks01In, int bricks12In,
        int bricks23In, int bricks34In)
        : name(nameIn), level(levelIn), maxLevel(maxLevelIn), frozen(false),
        bricks01(bricks01In), bricks12(bricks12In), bricks23(bricks23In),
        bricks34(bricks34In) {
            std::pair<int,int> tempPosition = std::make_pair(0,0);
            position = tempPosition;
        }

    //Prints out unit's level and abilities in the following format:
    //Ability (Magnitude if not 1)
    /* i.e
    AlphaBot Level 3:
    move 2, decon repair

    ExtendoBot Level 2:
    move 1, decon R2
    */
    const void printInfo() const;

    //Returns unit's name
    const std::string getName() const;

    //Returns unit's move ability
    const std::string getMove() const;

    //Set unit's move ability
    void setMove(const std::vector<int> &movementIn);

    //Returns unit's abilities as a string
    const std::string getAbility() const;

    //Returns if unit can decon
    const bool ifDecon() const;

    //Returns if unit can repair
    const bool ifRepair() const;

    //Returns if unit can carry
    const bool ifCarry() const;

    //Returns if unit can eat
    const bool ifEat() const;

    //Returns if unit can scare
    const bool ifScare() const;

    //Returns if unit can web
    const bool ifWeb() const;

    //Sets unit's abilities
    void setAbility(const std::vector<bool> &ability);

    //Sets unit's decon ability
    void setDecon(const std::pair<int,int> &decon);

    //Returns unit's level
    const int getLevel() const;

    //Sets unit's level
    void setLevel(const int levelIn);

    //Returns unit's max level
    const int getMaxLevel() const;

    //Returns bricks making up unit in a vector of ints
    const std::vector<int> getBricks() const;

    //Sets bricks making up max level unit
    void setBricks(const std::vector<int> &bricksIn);

    //Returns unit's bricks needed to go from level x-1 to x
    const std::vector<int> getLevelBricks(int x) const;

    //Returns if unit is frozen or webbed
    const bool ifFrozen();

    //Function to deconstruct unit. Does not care if unit is level 1, differentiation
    //is done later.
    virtual void getDecon() = 0;

    //Function to repair unit
    virtual void getRepair() = 0;

    //Function to eat input unit
    void eat(Unit &unit);

    //Function to freeze input unit (scare and web)
    void freeze(Unit &unit) const;

    //Function to get unit's position on arena
    const std::pair<int,int> getPosition() const;

    //Function to set unit's position on arena. Used for all forms of movement action,
    //game figures out legal moves given unit's movement action.
    void setPosition(int rowIn, int colIn);

private:
    std::string name;           //Unit's name
    int level;                  //Current level
    int maxLevel;               //Maximum level possible
    bool frozen;                //Whether unit has been frozen or webbed
    std::vector<int> movement;  //Described above
    std::vector<int> bricks;    //Bricks making up max level unit
    std::vector<bool> ability; //Described above
    std::pair<int,int> decon;  //Deconstruct magnitude and range
    std::pair<int,int> position;    //Position on the arena
    int bricks01;  //Number of bricks needed to go from level 0 to 1
    int bricks12;  //Number of bricks needed to go from level 1 to 2
    int bricks23;  //Number of bricks needed to go from level 2 to 3
    int bricks34;  //Number of bricks needed to go from level 3 to 4
};

//----------------------------Aero Unit Declarations-------------------------------------
class AirCab : public Unit {
public:
    //Constructor creates unit of highest level
    AirCab()
        : Unit("AirCab", 2, 2, 2, 2, 0, 0) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,7,4,15};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }

private:
};

class AirScout : public Unit {
public:
    AirScout()
        : Unit("AirScout", 2, 2, 1, 3, 0, 0) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{23,15,19,19};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::pair<int,int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

private:
};

class Hoverall : public Unit {
public:
    //Constructor creates unit of highest level
    //Unit(std::string nameIn, int levelIn, int maxLevelIn, int bricks01In, int bricks12In,
    //int bricks23In, int bricks34In)
    Hoverall()
        : Unit("Hoverall", 3, 3, 3, 6, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,6,6,14,14,15,15,17,17,36,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }
    }

private:
};

//----------------------------Auto Unit Declarations-------------------------------------
//----------------------------Robo Unit Declarations-------------------------------------
//----------------------------Wild Unit Declarations-------------------------------------
//----------------------------Dragon Unit Declarations-----------------------------------
//----------------------------Monster Unit Declarations----------------------------------
//----------------------------Arachno Unit Declarations----------------------------------
//----------------------------Aqua Unit Declarations-------------------------------------
#endif
