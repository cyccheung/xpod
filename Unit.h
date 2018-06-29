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
Ints containing the number of parts needed to go between levels use these
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
        : Unit("Air Cab", 2, 2, 2, 0, 0) {
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
    Unit(std::string nameIn, int levelIn, int bricks01In, int bricks12In,
        int bricks23In, int bricks34In)
        : name(nameIn), level(levelIn), maxLevel(levelIn), frozen(false),
        bricks01(bricks01In), bricks12(bricks12In), bricks23(bricks23In),
        bricks34(bricks34In) {
            std::pair<int,int> tempPosition = std::make_pair(-1,-1);
            position = tempPosition;
        }

    //Virtual destructor for Unit base class
    virtual ~Unit() {}

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
        : Unit("Air Cab", 2, 2, 2, 0, 0) {
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
        : Unit("Air Scout", 2, 1, 3, 0, 0) {
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
        : Unit("Cargo Copter", 3, 1, 3, 1, 0) {
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
        : Unit("Copter Raider", 3, 2, 3, 1, 0) {
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
        : Unit("Defense Station", 2, 1, 3, 0, 0) {
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
        : Unit("Flit", 1, 2, 0, 0, 0) {
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
        : Unit("Glider Medic", 2, 1, 4, 0, 0) {
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
        : Unit("Ground Medic", 2, 3, 1, 0, 0) {
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
        : Unit("Ground Control", 2, 2, 3, 0, 0) {
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
            : Unit("Hopper", 2, 1, 2, 0, 0) {
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
        : Unit("Hoverall", 3, 3, 6, 2, 0) {
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
            : Unit("Interceptor", 2, 1, 2, 0, 0) {
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
            : Unit("Jet Ambulance", 3, 1, 4, 3, 0) {
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
        : Unit("Jet Copter Raider", 3, 3, 4, 1, 0) {
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
            : Unit("Jet Raider", 3, 1, 3, 2, 0) {
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
        : Unit("Jump Jet", 2, 2, 4, 0, 0) {
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

class Minicopter : public Unit {
public:
    //Constructor creates unit of highest level
    Minicopter()
        : Unit("Minicopter", 2, 2, 2, 0, 0) {
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
            : Unit("Mini Jet Raider", 2, 1, 4, 0, 0) {
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
        : Unit("Repair Crew", 2, 1, 3, 0, 0) {
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
            : Unit("Rescue Jet", 2, 1, 3, 0, 0) {
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
        : Unit("Shuttle", 2, 1, 4, 0, 0) {
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
        : Unit("Skimmer", 1, 2, 0, 0, 0) {
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
        : Unit("Turbo Jet", 3, 3, 2, 1, 0) {
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
            : Unit("Wing Copter", 3, 2, 3, 2, 0) {
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
            : Unit("Wing Raider", 3, 2, 3, 1, 0) {
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
        : Unit("Air Horn", 2, 2, 3, 0, 0) {
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
        : Unit("Armored Sled", 3, 3, 2, 2, 0) {
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
        : Unit("Basher", 2, 3, 4, 0, 0) {
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
        : Unit("BXP 100", 2, 1, 2, 0, 0) {
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
        : Unit("BXP 200", 3, 1, 2, 3, 0) {
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
        : Unit("Crane", 2, 1, 2, 0, 0) {
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
        : Unit("Dozer", 3, 1, 5, 3, 0) {
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

class Dragster : public Unit {
public:
    //Constructor creates unit of highest level
    Dragster()
        : Unit("Dragster", 3, 4, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{5,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,2,36,36,6,29,35,42,42,6,8,8};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{5,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Flatbed : public Unit {
public:
    //Constructor creates unit of highest level
    Flatbed()
        : Unit("Flatbed", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,2,7,28};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
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
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Forklift : public Unit {
public:
    //Constructor creates unit of highest level
    Forklift()
        : Unit("Forklift", 2, 1, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{21,2};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class GoKart : public Unit {
public:
    //Constructor creates unit of highest level
    GoKart()
        : Unit("Go-Kart", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,8,14,36};
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

class HoverPod : public Unit {
public:
    //Constructor creates unit of highest level
    HoverPod()
        : Unit("Hover Pod", 2, 3, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{5,12,12,7,28};
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
            std::vector<int> tempMove{1,0,0,0};
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

class HoverSport : public Unit {
public:
    //Constructor creates unit of highest level
    HoverSport()
        : Unit("Hover Sport", 2, 4, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,6,12,12,7,28,29};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class HoverTruck : public Unit {
public:
    //Constructor creates unit of highest level
    HoverTruck()
        : Unit("Hover Truck", 2, 4, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,6,12,12,2,7,28};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class LaserBuggy : public Unit {
public:
    //Constructor creates unit of highest level
    LaserBuggy()
        : Unit("Laser Buggy", 3, 3, 3, 5, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,29,2,42,42,8,33,36,36,36};
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
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
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
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
    }
private:
};

class MultiStation : public Unit {
public:
    //Constructor creates unit of highest level
    MultiStation()
        : Unit("Multi-Station", 2, 3, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{5,6,6,8,14,33,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,true,false,false,false};
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
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Pushabout : public Unit {
public:
    //Constructor creates unit of highest level
    Pushabout()
        : Unit("Pushabout", 3, 1, 2, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,3};
            setMove(tempMove);
            std::vector<int> tempBricks{2,12,42,8};
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
            std::vector<int> tempMove{0,0,0,2};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,2};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,0,3};
            setMove(tempMove);
        }
    }
private:
};

class RocketRacer : public Unit {
public:
    //Constructor creates unit of highest level
    RocketRacer()
        : Unit("Rocket Racer", 3, 1, 3, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,6,36,36,12};
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

class Rollabout : public Unit {
public:
    //Constructor creates unit of highest level
    Rollabout()
        : Unit("Rollabout", 3, 1, 1, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{7,42,8};
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

class Semi : public Unit {
public:
    //Constructor creates unit of highest level
    Semi()
        : Unit("Semi", 3, 3, 4, 4, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,6,6,7,28,42,42,14,14,21,21};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
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
        else if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Speedster : public Unit {
public:
    //Constructor creates unit of highest level
    Speedster()
        : Unit("Speedster", 3, 1, 5, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,42,42,35,28,7,12,28};
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
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Spike : public Unit {
public:
    //Constructor creates unit of highest level
    Spike()
        : Unit("Spike", 3, 1, 2, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,12,42,33,35};
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
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
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
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Toboggan : public Unit {
public:
    //Constructor creates unit of highest level
    Toboggan()
        : Unit("Toboggan", 2, 3, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,6,7,7,35};
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
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }
private:
};
//----------------------------Robo Unit Declarations-------------------------------------
class AlphaBot : public Unit {
public:
    //Constructor creates unit of highest level
    AlphaBot()
        : Unit("AlphaBot", 3, 6, 6, 5, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,25,14,14,21,21,7,11,12,20,22,41,7,14,29,36,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
        else if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class BlasterBot : public Unit {
public:
    //Constructor creates unit of highest level
    BlasterBot()
        : Unit("BlasterBot", 3, 7, 2, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,15,15,11,11,12,13,29,7,13};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
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
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class BrainBot : public Unit {
public:
    //Constructor creates unit of highest level
    BrainBot()
        : Unit("BrainBot", 3, 1, 3, 5, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{25,9,11,11,43,18,22,36,36};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
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
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class ClawBot : public Unit {
public:
    //Constructor creates unit of highest level
    ClawBot()
        : Unit("ClawBot", 2, 8, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{7,7,14,14,15,15,36,36,18,18};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Cyclops : public Unit {
public:
    //Constructor creates unit of highest level
    Cyclops()
        : Unit("Cyclops", 3, 3, 7, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,25,9,14,14,15,15,29,36,22};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class DrRobot : public Unit {
public:
    //Constructor creates unit of highest level
    DrRobot()
        : Unit("Dr. Robot", 3, 3, 5, 4, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{9,25,29,14,15,22,36,43,14,14,27,27};
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
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class ExtendoBot : public Unit {
public:
    //Constructor creates unit of highest level
    ExtendoBot()
        : Unit("ExtendoBot", 2, 3, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,14,15,13,14,15,36};
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

class Fixit : public Unit {
public:
    //Constructor creates unit of highest level
    Fixit()
        : Unit("Fixit", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,20,36,43};
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
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Gearhead : public Unit {
public:
    //Constructor creates unit of highest level
    Gearhead()
        : Unit("Gearhead", 2, 1, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{25,15};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Grappler : public Unit {
public:
    //Constructor creates unit of highest level
    Grappler()
        : Unit("Grappler", 3, 1, 4, 4, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,14,27,43,7,7,10,36};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class JumpBot : public Unit {
public:
    //Constructor creates unit of highest level
    JumpBot()
        : Unit("JumpBot", 3, 5, 3, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,27,27,43,43,7,7,9,20};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class K9RovR : public Unit {
public:
    //Constructor creates unit of highest level
    K9RovR()
        : Unit("K9 Rov-R", 3, 3, 2, 6, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{27,20,36,6,41,14,14,14,14,43,43};
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
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class KnightBot : public Unit {
public:
    //Constructor creates unit of highest level
    KnightBot()
        : Unit("KnightBot", 3, 7, 2, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,1};
            setMove(tempMove);
            std::vector<int> tempBricks{7,7,12,25,29,36,36,10,11,18,41};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Lancer : public Unit {
public:
    //Constructor creates unit of highest level
    Lancer()
        : Unit("Lancer", 3, 5, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,14,14,21,21,7,7,6,14,14,11,29,41};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
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
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
    }
private:
};

class Lifter : public Unit {
public:
    //Constructor creates unit of highest level
    Lifter()
        : Unit("Lifter", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,15,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Longshot : public Unit {
public:
    //Constructor creates unit of highest level
    Longshot()
        : Unit("Longshot", 3, 3, 2, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{9,25,29,13,13,41};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,3);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,3);
            setDecon(tempDecon);
        }
    }
private:
};

class Microhopper : public Unit {
public:
    //Constructor creates unit of highest level
    Microhopper()
        : Unit("Microhopper", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{27,14,15,22};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class NiceBot : public Unit {
public:
    //Constructor creates unit of highest level
    NiceBot()
        : Unit("NiceBot", 3, 5, 3, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{7,7,7,21,21,7,7,29,13,15};
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
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::vector<bool> tempAbility{true,true,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Patroller : public Unit {
public:
    //Constructor creates unit of highest level
    Patroller()
        : Unit("Patroller", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{25,13,36,36};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class PestBot : public Unit {
public:
    //Constructor creates unit of highest level
    PestBot()
        : Unit("PestBot", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,21,36};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class RollerBot : public Unit {
public:
    //Constructor creates unit of highest level
    RollerBot()
        : Unit("RollerBot", 3, 7, 3, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,7,7,22,22,25,25,6,27,27,36,36};
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
            std::vector<int> tempMove{1,0,0,0};
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

class Sparks : public Unit {
public:
    //Constructor creates unit of highest level
    Sparks()
        : Unit("Sparks", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,18,27,43};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class TuffBot : public Unit {
public:
    //Constructor creates unit of highest level
    TuffBot()
        : Unit("TuffBot", 3, 4, 1, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,1};
            setMove(tempMove);
            std::vector<int> tempBricks{7,7,25,29,22,13};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,1};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {}
    }
private:
};
//----------------------------Wild Unit Declarations-------------------------------------
class Ant : public Unit {
public:
    //Constructor creates unit of highest level
    Ant()
        : Unit("Ant", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,36};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class BabyGiantSquid : public Unit {
public:
    //Constructor creates unit of highest level
    BabyGiantSquid()
        : Unit("Baby Giant Squid", 2, 5, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,14,14,36,36,26};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class BabyRattler : public Unit {
public:
    //Constructor creates unit of highest level
    BabyRattler()
        : Unit("Baby Rattler", 2, 2, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{11,19,40};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class BarnOwl : public Unit {
public:
    //Constructor creates unit of highest level
    BarnOwl()
        : Unit("Barn Owl", 2, 2, 5, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,15,16,16,19,19,23};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Bullfrog : public Unit {
public:
    //Constructor creates unit of highest level
    Bullfrog()
        : Unit("Bullfrog", 3, 5, 2, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,13,26,36,36,13,25,15};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Chimp : public Unit {
public:
    //Constructor creates unit of highest level
    Chimp()
        : Unit("Chimp", 3, 4, 4, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,6,11,26,14,14,15,15,11,11};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
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
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Croc : public Unit {
public:
    //Constructor creates unit of highest level
    Croc()
        : Unit("Croc", 3, 5, 5, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,15,24,36,36,2,11,11,19,19,2};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
        else if(getLevel() == 2) {}
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
        else if(getLevel() == 3) {}
    }
private:
};

class Flea : public Unit {
public:
    //Constructor creates unit of highest level
    Flea()
        : Unit("Flea", 2, 3, 7, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,3,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{11,13,25,13,39,39,36,36,40,40};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,3,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Gorilla : public Unit {
public:
    //Constructor creates unit of highest level
    Gorilla()
        : Unit("Gorilla", 3, 5, 5, 4, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,11,36,36,26,11,14,14,15,15,11,11,19,19};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
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
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Kanga : public Unit {
public:
    //Constructor creates unit of highest level
    Kanga()
        : Unit("Kanga", 3, 6, 6, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,13,15,17,17,23,7,11,15,15,14,14,11,19,19};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class KingCrab : public Unit {
public:
    //Constructor creates unit of highest level
    KingCrab()
        : Unit("King Crab", 3, 5, 4, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,14,14,40,40,11,11,11,11,16,16};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
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
        else if(getLevel() == 3) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Ladybug : public Unit {
public:
    //Constructor creates unit of highest level
    Ladybug()
        : Unit("Ladybug", 2, 1, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{11,16,16,36,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
        }
    }
private:
};

class Mantis : public Unit {
public:
    //Constructor creates unit of highest level
    Mantis()
        : Unit("Mantis", 2, 2, 5, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,3,13,15,15,36,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class Minnow : public Unit {
public:
    //Constructor creates unit of highest level
    Minnow()
        : Unit("Minnow", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{24,36};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Moth : public Unit {
public:
    //Constructor creates unit of highest level
    Moth()
        : Unit("Moth", 2, 5, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{13,39,39,36,36,17,17};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
        }
    }
private:
};

class PoisonMushroom : public Unit {
public:
    //Constructor creates unit of highest level
    PoisonMushroom()
        : Unit("Poison Mushroom", 1, 4, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{36,36,36,39};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Rattler : public Unit {
public:
    //Constructor creates unit of highest level
    Rattler()
        : Unit("Rattler", 2, 2, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{11,19,11,40};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Scorpion : public Unit {
public:
    //Constructor creates unit of highest level
    Scorpion()
        : Unit("Scorpion", 2, 3, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{11,14,15,13};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class Spider : public Unit {
public:
    //Constructor creates unit of highest level
    Spider()
        : Unit("Spider", 2, 4, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,15,36,36,14,14,14,14};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class StingingAnt : public Unit {
public:
    //Constructor creates unit of highest level
    StingingAnt()
        : Unit("Stinging Ant", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,36,40};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Tadpole : public Unit {
public:
    //Constructor creates unit of highest level
    Tadpole()
        : Unit("Tadpole", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,36};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Treefrog : public Unit {
public:
    //Constructor creates unit of highest level
    Treefrog()
        : Unit("Treefrog", 2, 4, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,6,36,36,14,14,26};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Turtle : public Unit {
public:
    //Constructor creates unit of highest level
    Turtle()
        : Unit("Turtle", 2, 2, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,15,11};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
    }
private:
};
//----------------------------Dragon Unit Declarations-----------------------------------
class CaveBeetle : public Unit {
public:
    //Constructor creates unit of highest level
    CaveBeetle()
        : Unit("Cave Beetle", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,61,61};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Crawling : public Unit {
public:
    //Constructor creates unit of highest level
    Crawling()
        : Unit("Crawling", 1, 5, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,14,61,61,7};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class CuriousHatchling : public Unit {
public:
    //Constructor creates unit of highest level
    CuriousHatchling()
        : Unit("CuriousHatchling", 1, 4, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{20,20,3,71};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class DragonRunt : public Unit {
public:
    //Constructor creates unit of highest level
    DragonRunt()
        : Unit("DragonRunt", 2, 3, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,7,61,22};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
        }
    }
private:
};

class DragonSerpent : public Unit {
public:
    //Constructor creates unit of highest level
    DragonSerpent()
        : Unit("DragonSerpent", 2, 4, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,14,14,15,53,22,61,61};
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
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class DragonSlug : public Unit {
public:
    //Constructor creates unit of highest level
    DragonSlug()
        : Unit("Dragon Slug", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,16,71};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class FireCritter : public Unit {
public:
    //Constructor creates unit of highest level
    FireCritter()
        : Unit("Fire Critter", 1, 5, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{16,7,67,18,72};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class FireDragon : public Unit {
public:
    //Constructor creates unit of highest level
    FireDragon()
        : Unit("Fire Dragon", 4, 6, 10, 9, 6) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{15,14,44,36,61,61,1,26,51,67,67,69,45,14,18,72,6,14,14,15,15,53,53,62,62,16,16,14,54,61,61};
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
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,1,0};
            setMove(tempMove);
        }
        else if(getLevel() == 4) {
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
        }
    }
private:
};

class FireTrap : public Unit {
public:
    //Constructor creates unit of highest level
    FireTrap()
        : Unit("Fire Trap", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{20,72};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class LandDragon : public Unit {
public:
    //Constructor creates unit of highest level
    LandDragon()
        : Unit("Land Dragon", 4, 10, 6, 9, 8) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{16,16,3,22,22,7,62,62,36,36,15,14,14,54,1,6,6,67,14,14,15,15,53,53,26,6,67,20,72,61,61,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
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
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
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
        else if(getLevel() == 4) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class LizardMan : public Unit {
public:
    //Constructor creates unit of highest level
    LizardMan()
        : Unit("Lizard Man", 2, 5, 5, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,15,6,44,16,6,14,67,68,73};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Snakeling : public Unit {
public:
    //Constructor creates unit of highest level
    Snakeling()
        : Unit("Snakeling", 2, 4, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,7,45,73,14,61};
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
            std::vector<int> tempMove{1,0,0,0};
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

class StormDragon : public Unit {
public:
    //Constructor creates unit of highest level
    StormDragon()
        : Unit("Storm Dragon", 4, 10, 10, 6, 4) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
            std::vector<int> tempBricks{15,14,14,22,45,45,36,36,61,61,14,18,22,1,3,16,51,26,20,20,14,14,15,15,53,53,62,62,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
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
        else if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
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
            std::vector<int> tempMove{0,0,2,0};
            setMove(tempMove);
        }
        else if(getLevel() == 4) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class ThunderDragon : public Unit {
public:
    //Constructor creates unit of highest level
    ThunderDragon()
        : Unit("Thunder Dragon", 4, 9, 12, 4, 4) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,2,2};
            setMove(tempMove);
            std::vector<int> tempBricks{3,3,36,36,71,26,20,20,15,14,14,14,6,1,15,7,62,62,51,69,45,16,16,14,54,22,22,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
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
            std::vector<int> tempMove{0,0,0,1};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,1,2};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,1};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,1,2};
            setMove(tempMove);
        }
        else if(getLevel() == 4) {
            std::vector<int> tempMove{0,0,2,2};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Wyrm : public Unit {
public:
    //Constructor creates unit of highest level
    Wyrm()
        : Unit("Wyrm", 2, 2, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,54,20,72,26,71};
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

class YoungHatchling : public Unit {
public:
    //Constructor creates unit of highest level
    YoungHatchling()
        : Unit("Young Hatchling", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{20,18};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};
//----------------------------Monster Unit Declarations----------------------------------
class BigMouth : public Unit {
public:
    //Constructor creates unit of highest level
    BigMouth()
        : Unit("Big Mouth", 3, 7, 7, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{62,62,1,50,50,36,36,69,64,24,24,14,14,50,67,67,15};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class Bucky : public Unit {
public:
    //Constructor creates unit of highest level
    Bucky()
        : Unit("Bucky", 2, 5, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,50,69,69,64,24,7,61,61};
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
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class CreepieCrawly : public Unit {
public:
    //Constructor creates unit of highest level
    CreepieCrawly()
        : Unit("Creepie Crawly", 1, 2, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,14};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Dizzy : public Unit {
public:
    //Constructor creates unit of highest level
    Dizzy()
        : Unit("Dizzy", 3, 3, 4, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{65,58,47,15,3,36,36,62,62};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class Eyeball : public Unit {
public:
    //Constructor creates unit of highest level
    Eyeball()
        : Unit("Eyeball", 3, 3, 2, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{15,58,47,65,36,39,66,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }
    }
private:
};

class EyeBeamer : public Unit {
public:
    //Constructor creates unit of highest level
    EyeBeamer()
        : Unit("Eye Beamer", 3, 4, 7, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{64,66,39,36,50,50,50,50,12,14,14,69,67,67};
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
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
    }
private:
};

class Eyestalk : public Unit {
public:
    //Constructor creates unit of highest level
    Eyestalk()
        : Unit("Eyestalk", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,10,61};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Frightful : public Unit {
public:
    //Constructor creates unit of highest level
    Frightful()
        : Unit("Frightful", 3, 5, 6, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,50,69,69,64,1,70,36,36,14,14,14,14};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
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
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
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
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Gremlin : public Unit {
public:
    //Constructor creates unit of highest level
    Gremlin()
        : Unit("Gremlin", 2, 2, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{15,50,70};
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
        if(getLevel() == 1) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
    }
private:
};

class GremlinHotfoot : public Unit {
public:
    //Constructor creates unit of highest level
    GremlinHotfoot()
        : Unit("Gremlin Hotfoot", 2, 4, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,50,15,70,62,62};
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
            std::vector<int> tempMove{1,0,0,0};
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

class GremlinKing : public Unit {
public:
    //Constructor creates unit of highest level
    GremlinKing()
        : Unit("Gremlin King", 3, 6, 6, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,6,14,14,15,15,6,12,15,70,67,67,62,62};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class GremlinPorter : public Unit {
public:
    //Constructor creates unit of highest level
    GremlinPorter()
        : Unit("Gremlin Porter", 2, 3, 1, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,6,15,70};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,false,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
    }
private:
};

class Hoppy : public Unit {
public:
    //Constructor creates unit of highest level
    Hoppy()
        : Unit("Hoppy", 2, 8, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{64,36,36,36,36,61,61,69,65,66};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
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
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class HypnoThing : public Unit {
public:
    //Constructor creates unit of highest level
    HypnoThing()
        : Unit("Hypno Thing", 3, 2, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{14,15,65,66,39,36,69,6,67,67};
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
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,2);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class It : public Unit {
public:
    //Constructor creates unit of highest level
    It()
        : Unit("It", 3, 3, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,15,15,14,10,10,67,67,66,39,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }
    }
private:
};

class Jumpy : public Unit {
public:
    //Constructor creates unit of highest level
    Jumpy()
        : Unit("Jumpy", 3, 2, 3, 5, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{64,70,50,69,70,6,14,14,15,54};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
        else if(getLevel() == 2) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class LittleOneEye : public Unit {
public:
    //Constructor creates unit of highest level
    LittleOneEye()
        : Unit("Little One Eye", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,10,61};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class MonsterSurgeon : public Unit {
public:
    //Constructor creates unit of highest level
    MonsterSurgeon()
        : Unit("Monster Surgeon", 2, 7, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,50,50,15,15,67,67,14,14,14,14};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,false};
            setAbility(tempAbility);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{true,false,false,false,false};
            setAbility(tempAbility);
        }
    }
private:
};

class NurseScarem : public Unit {
public:
    //Constructor creates unit of highest level
    NurseScarem()
        : Unit("Nurse Scarem", 2, 7, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{65,10,10,36,36,24,61,58,47,15};
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
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Slither : public Unit {
public:
    //Constructor creates unit of highest level
    Slither()
        : Unit("Slither", 3, 4, 3, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,15,62,62,15,14,54,14,6,6};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
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
            std::vector<int> tempMove{1,0,0,0};
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
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Smiler : public Unit {
public:
    //Constructor creates unit of highest level
    Smiler()
        : Unit("Smiler", 3, 6, 5, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{15,3,62,62,36,36,24,24,6,50,12,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,true,false};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};
//----------------------------Arachno Unit Declarations----------------------------------
class Biter : public Unit {
public:
    //Constructor creates unit of highest level
    Biter()
        : Unit("Biter", 1, 6, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{17,50,58,14,61,46};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class BlackWidow : public Unit {
public:
    //Constructor creates unit of highest level
    BlackWidow()
        : Unit("Black Widow", 3, 4, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,44,44,54,41,41,41,41,9,41,41,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,true};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,false,false,true};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Bugling : public Unit {
public:
    //Constructor creates unit of highest level
    Bugling()
        : Unit("Bugling", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,22,34};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Cricket : public Unit {
public:
    //Constructor creates unit of highest level
    Cricket()
        : Unit("Cricket", 3, 2, 6, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{23,49,19,19,40,40,61,61,28,7};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class GrandaddyLongLegs : public Unit {
public:
    //Constructor creates unit of highest level
    GrandaddyLongLegs()
        : Unit("Grandaddy Long Legs", 3, 4, 8, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,49,55,55,19,19,40,40,41,41,41,41,41,41,23};
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
            std::vector<int> tempMove{4,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Hatchling : public Unit {
public:
    //Constructor creates unit of highest level
    Hatchling()
        : Unit("Hatchling", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{50,14,58};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Jumper : public Unit {
public:
    //Constructor creates unit of highest level
    Jumper()
        : Unit("Jumper", 2, 3, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{17,17,9,28,34,36};
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
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class PoisonBug : public Unit {
public:
    //Constructor creates unit of highest level
    PoisonBug()
        : Unit("Poison Bug", 3, 3, 5, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{23,2,7,60,40,40,61,61,9,36,41};
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
        }
        else if(getLevel() == 2) {
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
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Scuttler : public Unit {
public:
    //Constructor creates unit of highest level
    Scuttler()
        : Unit("Scuttler", 2, 5, 2, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,55,55,61,61,41,41};
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
            std::vector<int> tempMove{1,0,0,0};
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

class SlingerHatchling : public Unit {
public:
    //Constructor creates unit of highest level
    SlingerHatchling()
        : Unit("SlingerHatchling", 1, 5, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{54,50,58,41,41};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,false,false,true};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class StickleBack : public Unit {
public:
    //Constructor creates unit of highest level
    StickleBack()
        : Unit("Stickle Back", 1, 4, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{44,36,41,41};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Stinger : public Unit {
public:
    //Constructor creates unit of highest level
    Stinger()
        : Unit("Stinger", 1, 5, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{44,61,14,54,41};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class Tickler : public Unit {
public:
    //Constructor creates unit of highest level
    Tickler()
        : Unit("Tickler", 3, 3, 4, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{49,17,17,14,14,40,40,41,41};
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
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class UncleLongLegs : public Unit {
public:
    //Constructor creates unit of highest level
    UncleLongLegs()
        : Unit("Uncle Long Legs", 3, 6, 4, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,23,19,19,40,40,41,41,41,41,41,41};
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
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class VenemousNettler : public Unit {
public:
    //Constructor creates unit of highest level
    VenemousNettler()
        : Unit("Venemous Nettler", 2, 4, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{2,60,22,55,44,41,41,34};
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
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};
//----------------------------Aqua Unit Declarations-------------------------------------
class ElectricEel : public Unit {
public:
    //Constructor creates unit of highest level
    ElectricEel()
        : Unit("Electric Eel", 2, 4, 6, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{44,46,59,55,6,6,44,61,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class Flounder : public Unit {
public:
    //Constructor creates unit of highest level
    Flounder()
        : Unit("Flounder", 2, 5, 5, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{44,46,46,59,59,28,44,52,27,75};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class FlyingFish : public Unit {
public:
    //Constructor creates unit of highest level
    FlyingFish()
        : Unit("Flying Fish", 2, 1, 3, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,44,44,36};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class GreatWhite : public Unit {
public:
    //Constructor creates unit of highest level
    GreatWhite()
        : Unit("GreatWhite", 3, 6, 4, 3, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,28,76,76,62,62,74,6,6,27,38,52,52,26};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
        else if(getLevel() == 2) {
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::pair<int, int> tempDecon = std::make_pair(2,1);
            setDecon(tempDecon);
        }
    }
private:
};

class Guppy : public Unit {
public:
    //Constructor creates unit of highest level
    Guppy()
        : Unit("Guppy", 2, 4, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{29,27,27,26,52,52,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Hammerhead : public Unit {
public:
    //Constructor creates unit of highest level
    Hammerhead()
        : Unit("Hammerhead", 3, 8, 4, 5, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,2};
            setMove(tempMove);
            std::vector<int> tempBricks{29,6,62,62,46,46,59,59,1,28,74,38,3,27,27,61,61};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,0,0,2};
            setMove(tempMove);
        }
    }
private:
};

class HermitCrab : public Unit {
public:
    //Constructor creates unit of highest level
    HermitCrab()
        : Unit("Hermit Crab", 2, 2, 6, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{76,7,44,46,46,56,56,55};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class LampreyEel : public Unit {
public:
    //Constructor creates unit of highest level
    LampreyEel()
        : Unit("Lamprey Eel", 2, 3, 4, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,61,61,6,44,44,55};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{3,0,0,0};
            setMove(tempMove);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
        }
    }
private:
};

class ManOWar : public Unit {
public:
    //Constructor creates unit of highest level
    ManOWar()
        : Unit("Man-O-War", 2, 6, 6, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,28,46,46,52,52,29,29,6,6,4,4};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
        }
    }
private:
};

class Piranha : public Unit {
public:
    //Constructor creates unit of highest level
    Piranha()
        : Unit("Piranha", 2, 2, 5, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{6,28,61,61,62,62,52};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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

class Plankton : public Unit {
public:
    //Constructor creates unit of highest level
    Plankton()
        : Unit("Plankton", 1, 1, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{61};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class PoisonAnemone : public Unit {
public:
    //Constructor creates unit of highest level
    PoisonAnemone()
        : Unit("Poison Anemone", 2, 3, 8, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{3,29,29,46,46,46,46,59,59,59,59};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(1,1);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
    }
private:
};

class Porpoise : public Unit {
public:
    //Constructor creates unit of highest level
    Porpoise()
        : Unit("Porpoise", 3, 4, 2, 2, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,2};
            setMove(tempMove);
            std::vector<int> tempBricks{1,74,28,76,62,62,3,38};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
            std::vector<int> tempMove{1,0,0,1};
            setMove(tempMove);
        }
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,1};
            setMove(tempMove);
        }
        else if(getLevel() == 3) {
            std::vector<int> tempMove{0,2,0,2};
            setMove(tempMove);
        }
    }
private:
};

class SeaHorse : public Unit {
public:
    //Constructor creates unit of highest level
    SeaHorse()
        : Unit("Sea Horse", 1, 4, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{62,46,28,52};
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
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
    }
private:
};

class SeaSnail : public Unit {
public:
    //Constructor creates unit of highest level
    SeaSnail()
        : Unit("Sea Snail", 3, 1, 2, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,29,76,60};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class SeaSlug : public Unit {
public:
    //Constructor creates unit of highest level
    SeaSlug()
        : Unit("Sea Slug", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{62,27,10};
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
        if(getLevel() == 1) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
    }
private:
};

class Shrimp : public Unit {
public:
    //Constructor creates unit of highest level
    Shrimp()
        : Unit("Shrimp", 1, 3, 0, 0, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{1,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{27,52,36};
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
        if(getLevel() == 1) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {}
    }
private:
};

class Stingray : public Unit {
public:
    //Constructor creates unit of highest level
    Stingray()
        : Unit("Stingray", 3, 3, 4, 1, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{1,76,76,27,27,55,55,60};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,false,true,false,false};
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
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{0,2,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {}
    }
private:
};

class SeaTortoise : public Unit {
public:
    //Constructor creates unit of highest level
    SeaTortoise()
        : Unit("Sea Tortoise", 3, 3, 3, 4, 0) {
            //<move, jump, fly, push>
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<int> tempBricks{76,76,7,60,55,10,62,62,62,62};
            setBricks(tempBricks);
            std::pair<int, int> tempDecon = std::make_pair(0,0);
            setDecon(tempDecon);
            //<Repair, Carry, Eat, Scare, Web>
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }

    //Deconstructs this unit
    void getDecon() {
        setLevel(getLevel() - 1);
        if(getLevel() == 1) {
            std::vector<int> tempMove{0,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,false,true,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 2) {}
    }

    //Repairs this unit
    void getRepair() {
        setLevel(getLevel() + 1);
        if(getLevel() == 2) {
            std::vector<int> tempMove{2,0,0,0};
            setMove(tempMove);
            std::vector<bool> tempAbility{false,true,true,false,false};
            setAbility(tempAbility);
        }
        else if(getLevel() == 3) {}
    }
private:
};
#endif
