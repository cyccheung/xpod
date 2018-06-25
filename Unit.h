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
Repair, Carry, Eat, Web, Scare
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

private:
};

*/

#include <string>
#include <vector>
#include <iostream>

class Unit {
public:
    //Default constructor for Unit
    Unit()
        : name("Default"), level(0), maxLevel(0), frozen(false), bricks01(0), bricks12(0),
        bricks23(0), bricks34(0) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{0};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
            std::pair<int,int> tempPosition = std::make_pair(-1,-1);
            position = tempPosition;
        }

    //Constructor for Unit
    Unit(std::string nameIn, int levelIn, int maxLevelIn, int bricks01In, int bricks12In,
        int bricks23In, int bricks34In)
        : name(nameIn), level(levelIn), maxLevel(maxLevelIn), frozen(false),
        bricks01(bricks01In), bricks12(bricks12In), bricks23(bricks23In),
        bricks34(bricks34In) {
            std::pair<int,int> tempPosition = std::make_pair(-1,-1);
            position = tempPosition;
        }

    //Virtual destructor for Unit base class
    virtual ~Unit() {}
/*
    //Copy constructor
    Unit(const Unit &other) {
        name = other.getName();
        level = other.getLevel();
        maxLevel = other.getMaxLevel();
        frozen = other.ifFrozen();
        movement = other.getMovement();
        bricks = other.getBricks();
        ability = other.getAbilities();
        decon = other.getDeconVect();
        position = other.getPosition();
        bricks01 = other.getLevelBricks(1);
        bricks12 = other.getLevelBricks(2) - other.getLevelBricks(1);
        bricks23 = other.getLevelBricks(3) - other.getLevelBricks(2) -
        other.getLevelBricks(1);
        bricks34 = other.getLevelBricks(4) - other.getLevelBricks(3) -
        other.getLevelBricks(2) - other.getLevelBricks(1);
    }
*/
    //Overload of assignment operator
    Unit& operator=(const Unit &other) {
        if(this == &other) {
            return *this;
        }
        this->name = other.getName();
        this->level = other.getLevel();
        this->maxLevel = other.getMaxLevel();
        this->frozen = other.ifFrozen();
        this->movement = other.getMovement();
        this->bricks = other.getBricks();
        this->ability = other.getAbilities();
        this->decon = other.getDeconVect();
        this->position = other.getPosition();
        this->bricks01 = other.getLevelBricks(1);
        this->bricks12 = other.getLevelBricks(2) - other.getLevelBricks(1);
        this->bricks23 = other.getLevelBricks(3) - other.getLevelBricks(2) -
        other.getLevelBricks(1);
        this->bricks34 = other.getLevelBricks(4) - other.getLevelBricks(3) -
        other.getLevelBricks(2) - other.getLevelBricks(1);
        return *this;
    }


    //Prints out unit's level and abilities in the following format:
    //Ability (Magnitude if not 1)
    /* i.e
    AlphaBot Level 3:
    move 2, decon repair
    Position: 3, 2

    ExtendoBot Level 2:
    move 1, decon R2
    Position: 2, 5

    ExtendoBot Level 2:
    move 1, decon R2
    Position: 3, 1
    Frozen
    */
    const void printInfo() const;

    //Returns unit's name
    const std::string getName() const;

    //Returns unit's move ability
    const std::string getMove() const;

    //Returns magnitude of unit's move ability
    const int getMoveMagnitude() const;

    //Returns unit's movement vector
    const std::vector<int> getMovement() const;

    //Set unit's move ability
    void setMove(const std::vector<int> &movementIn);

    //Returns unit's abilities as a string
    const std::string getAbility() const;

    //Returns unit's abilities as vector
    const std::vector<bool> getAbilities() const;

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

    //Returns unit's decon pair
    const std::pair<int,int> getDeconVect() const;

    //Returns unit's level
    int getLevel() const;

    //Sets unit's level
    void setLevel(const int levelIn);

    //Returns unit's max level
    const int getMaxLevel() const;

    //Returns bricks making up unit in a vector of ints
    const std::vector<int> getBricks() const;

    //Sets bricks making up max level unit
    void setBricks(const std::vector<int> &bricksIn);

    //Returns unit's bricks needed to go from level x-1 to x
    //const std::vector<int> getLevelBricks(int x) const;
    const int getLevelBricks(int x) const;

    //Returns if unit is frozen or webbed
    const bool ifFrozen() const;

    //Function to deconstruct unit. Does not care if unit is level 1, differentiation
    //is done later.
    virtual void getDecon() {
        return;
    }

    //Function to repair unit
    virtual void getRepair() {
        return;
    }

    //Function to eat input unit
    void eat(Unit &unit);

    //Function to freeze this unit (scare and web)
    void freeze();

    //Function to unfreeze this unit
    void unfreeze();

    //Function to get unit's position on arena
    const std::pair<int,int> getPosition() const;

    //Function to set unit's position on arena. Used for all forms of movement action,
    //game figures out legal moves given unit's movement action.
    void setPosition(const std::pair<int,int> &positionIn);

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

//Overload of == operator. Differentiate units based on position
bool operator==(const Unit &lhs, const Unit &rhs);

//Overload of != operator. Differentiate units based on position
bool operator!=(const Unit &lhs, const Unit &rhs);

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
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
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
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
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

class CargoCopter : public Unit {
public:
    //Constructor creates unit of highest level
    CargoCopter()
        : Unit("CargoCopter", 3, 3, 1, 3, 1, 0) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{32,23,24,24,31};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
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
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class CopterRaider : public Unit {
public:
    //Constructor creates unit of highest level
    CopterRaider()
        : Unit("CopterRaider", 3, 3, 2, 3, 1, 0) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,32,3,3,34,31};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
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
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class DefenseStation : public Unit {
public:
    //Constructor creates unit of highest level
    DefenseStation()
        : Unit("DefenseStation", 2, 2, 1, 3, 0, 0) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{32,13,30,30};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,3);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,3);
            setDecon(tempDecon);
        }
    }
private:
};

class Flit : public Unit {
public:
    //Constructor creates unit of highest level
    Flit()
        : Unit("Flit", 1, 1, 2, 0, 0, 0) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,15};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
    }
private:
};

class GliderMedic : public Unit {
public:
    //Constructor creates unit of highest level
    GliderMedic()
        : Unit("GliderMedic", 2, 2, 1, 4, 0, 0) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,17,17,30,30};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class GroundMedic : public Unit {
public:
    //Constructor creates unit of highest level
    GroundMedic()
        : Unit("GroundMedic", 2, 2, 3, 1, 0, 0) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,14,24,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class GroundControl : public Unit {
public:
    //Constructor creates unit of highest level
    GroundControl()
        : Unit("GroundControl", 2, 2, 2, 3, 0, 0) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,4,30,30,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Hopper : public Unit {
public:
    //Constructor creates unit of highest level
        Hopper()
            : Unit("Hopper", 2, 2, 1, 2, 0, 0) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{24,19,36};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{1,0,0,0};
                setMove(tempMove);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
            }
        }
private:
};

class Hoverall : public Unit {
public:
    //Constructor creates unit of highest level
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

class Interceptor : public Unit {
public:
    //Constructor creates unit of highest level
        Interceptor()
            : Unit("Interceptor", 2, 2, 1, 2, 0, 0) {
                std::vector<int> tempMove{0,0,1,0};
                setMove(tempMove);
                std::vector<int> tempBricks{13,24,24};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,1,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
            }
        }
private:
};

class JetAmbulance : public Unit {
public:
    //Constructor creates unit of highest level
        JetAmbulance()
            : Unit("JetAmbulance", 3, 3, 1, 4, 3, 0) {
                std::vector<int> tempMove{0,3,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{4,7,15,37,37,14,14,36};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{true,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 3) {
                std::vector<int> tempMove{0,3,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{true,false,false,false,false};
                setAbility(tempAbility);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
        }
private:
};

class JetCopterRaider : public Unit {
public:
    //Constructor creates unit of highest level
    JetCopterRaider()
        : Unit("JetCopterRaider", 3, 3, 3, 4, 1, 0) {
            std::vector<int> tempMove{0,0,3,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,19,19,2,34,37,37,31};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,3,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class JetRaider : public Unit {
public:
    //Constructor creates unit of highest level
        JetRaider()
            : Unit("JetRaider", 3, 3, 1, 3, 2, 0) {
                std::vector<int> tempMove{0,3,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{1,34,37,37,7,38};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 3) {
                std::vector<int> tempMove{0,3,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
            }
        }
private:
};

class JumpJet : public Unit {
public:
    //Constructor creates unit of highest level
    JumpJet()
        : Unit("JumpJet", 2, 2, 2, 4, 0, 0) {
            std::vector<int> tempMove{0,3,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,15,7,37,37,38};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,3,2,0};
            setMove(tempMove);
        }
    }
private:
};

class MiniCopter : public Unit {
public:
    //Constructor creates unit of highest level
    MiniCopter()
        : Unit("MiniCopter", 2, 2, 2, 2, 0, 0) {
            std::vector<int> tempMove{0,0,3,0};
            setMove(tempMove);
            std::vector<int> tempBricks{7,23,13,31};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,3,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class MiniJetRaider : public Unit {
public:
    //Constructor creates unit of highest level
        MiniJetRaider()
            : Unit("MiniJetRaider", 2, 2, 1, 4, 0, 0) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{34,7,15,37,37};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{0,2,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
            }
        }
private:
};

class RepairCrew : public Unit {
public:
    //Constructor creates unit of highest level
    RepairCrew()
        : Unit("RepairCrew", 2, 2, 1, 3, 0, 0) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,24,30,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class RescueJet : public Unit {
public:
    //Constructor creates unit of highest level
        RescueJet()
            : Unit("RescueJet", 2, 2, 1, 3, 0, 0) {
                std::vector<int> tempMove{0,0,1,0};
                setMove(tempMove);
                std::vector<int> tempBricks{6,19,30,36};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{true,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,1,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{true,false,false,false,false};
                setAbility(tempAbility);
            }
        }
private:
};

class Shuttle : public Unit {
public:
    //Constructor creates unit of highest level
    Shuttle()
        : Unit("Shuttle", 2, 2, 1, 4, 0, 0) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{34,17,17,30,30};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Skimmer : public Unit {
public:
    //Constructor creates unit of highest level
    Skimmer()
        : Unit("Skimmer", 1, 1, 2, 0, 0, 0) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{19,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
    }
private:
};

class TurboJet : public Unit {
public:
    //Constructor creates unit of highest level
    TurboJet()
        : Unit("TurboJet", 3, 3, 3, 2, 1, 0) {
            std::vector<int> tempMove{0,4,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,3,32,37,37,34};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() override {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() override {
        setLevel(getLevel() + 1);
        if(getLevel() == 3) {
            std::vector<int> tempMove{0,4,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class WingCopter : public Unit {
public:
    //Constructor creates unit of highest level
        WingCopter()
            : Unit("WingCopter", 3, 3, 2, 3, 2, 0) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
                std::vector<int> tempBricks{2,7,31,36,36,17,17};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 3) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
            }
        }
private:
};

class WingRaider : public Unit {
public:
    //Constructor creates unit of highest level
        WingRaider()
            : Unit("WingRaider", 3, 3, 2, 3, 1, 0) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
                std::vector<int> tempBricks{1,34,11,17,17,13};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() override {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
            else if(getLevel() == 2) {
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
            }
        }

        //Repairs this unit
        void getRepair() override {
            setLevel(getLevel() + 1);
            if(getLevel() == 3) {
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,2,0};
                setMove(tempMove);
            }
        }
private:
};

//----------------------------Auto Unit Declarations-------------------------------------
class AirHorn : public Unit {
public:
    //Constructor creates unit of highest level
    AirHorn()
        : Unit("Airhorn", 2, 2, 2, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,21,5,14,33};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
    }
private:
};

class ArmoredSled : public Unit {
public:
    //Constructor creates unit of highest level
    ArmoredSled()
        : Unit("ArmoredSled", 3, 3, 3, 2, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{21,21,28,28,7,36,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
        }
        else if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 3) {
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Basher : public Unit {
public:
    //Constructor creates unit of highest level
        Basher()
            : Unit("Basher", 2, 2, 3, 4, 0, 0) {
                //<move, jump, fly, push>
                std::vector<int> tempMove{1,0,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{2,5,29,6,33,36,36};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
            }
        }

        //Repairs this unit
        void getRepair() {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{1,0,0,0};
                setMove(tempMove);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
            }
        }
private:
};

class BXP100 : public Unit {
public:
    //Constructor creates unit of highest level
        BXP100()
            : Unit("BXP100", 2, 2, 1, 2, 0, 0) {
                //<move, jump, fly, push>
                std::vector<int> tempMove{2,0,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{8,6,6};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
            }
        }

        //Repairs this unit
        void getRepair() {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{2,0,0,0};
                setMove(tempMove);
            }
        }
private:
};

class BXP200 : public Unit {
public:
    //Constructor creates unit of highest level
        BXP200()
            : Unit("BXP200", 3, 3, 1, 2, 3, 0) {
                //<move, jump, fly, push>
                std::vector<int> tempMove{3,0,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{8,6,6,2,5,29};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{2,0,0,0};
                setMove(tempMove);
            }
        }

        //Repairs this unit
        void getRepair() {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{2,0,0,0};
                setMove(tempMove);
            }
            else if(getLevel() == 3) {
                std::vector<int> tempMove{3,0,0,0};
                setMove(tempMove);
            }
        }
private:
};

class Crane : public Unit {
public:
    //Constructor creates unit of highest level
        Crane()
            : Unit("Crane", 2, 2, 1, 2, 0, 0) {
                //<move, jump, fly, push>
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
                std::vector<int> tempBricks{5,14,33};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(1,1);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,true,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }
        }

        //Repairs this unit
        void getRepair() {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::pair<int, int> tempDecon = std::make_pair(1,2);
                setDecon(tempDecon);
                std::vector<bool> tempAbility{false,true,false,false,false};
                setAbility(tempAbility);
            }
        }
private:
};

class Dozer : public Unit {
public:
    //Constructor creates unit of highest level
        Dozer()
            : Unit("Dozer", 3, 3, 1, 5, 3, 0) {
                //<move, jump, fly, push>
                std::vector<int> tempMove{0,0,0,4};
                setMove(tempMove);
                std::vector<int> tempBricks{1,7,8,12,42,42,8,12,35};
                setBricks(tempBricks);
                std::pair<int, int> tempDecon = std::make_pair(0,0);
                setDecon(tempDecon);
                //<Repair, Carry, Eat, Scare, Web>
                std::vector<bool> tempAbility{false,false,false,false,false};
                setAbility(tempAbility);
            }

        //Deconstructs this unit
        void getDecon() {
            setLevel(getLevel() - 1);
            if(getLevel() == 1) {
                std::vector<int> tempMove{0,0,0,0};
                setMove(tempMove);
            }
            else if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,0,3};
                setMove(tempMove);
            }
        }

        //Repairs this unit
        void getRepair() {
            setLevel(getLevel() + 1);
            if(getLevel() == 2) {
                std::vector<int> tempMove{0,0,0,3};
                setMove(tempMove);
            }
            else if(getLevel() == 3) {
                std::vector<int> tempMove{0,0,0,4};
                setMove(tempMove);
            }
        }
private:
};
//----------------------------Robo Unit Declarations-------------------------------------
//----------------------------Wild Unit Declarations-------------------------------------
//----------------------------Dragon Unit Declarations-----------------------------------
//----------------------------Monster Unit Declarations----------------------------------
//----------------------------Arachno Unit Declarations----------------------------------
//----------------------------Aqua Unit Declarations-------------------------------------
#endif
