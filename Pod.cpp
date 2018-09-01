/*
Pod.cpp contains the constructors for the 8 pods. It fills the inventory vector with the
appropriate number of parts. Functions to add and remove a part from the inventory is
implemented here as well
*/

#include "Pod.h"
#include <cassert>
#include <iostream>

Pod::Pod(const std::string nameIn) {
    //Set pod's name (i.e Aero, Auto...)
    factionName = nameIn;
    inventory.push_back(0);
    if(nameIn == "Aero") {
        inventory.push_back(1); //1
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(2); //15
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //30
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
        //Fill up plansheet
        AirCab unit1;
        planSheet.push_back(unit1);
        AirScout unit2;
        planSheet.push_back(unit2);
        CargoCopter unit3;
        planSheet.push_back(unit3);
        CopterRaider unit4;
        planSheet.push_back(unit4);
        DefenseStation unit5;
        planSheet.push_back(unit5);
        Flit unit6;
        planSheet.push_back(unit6);
        GliderMedic unit7;
        planSheet.push_back(unit7);
        GroundMedic unit8;
        planSheet.push_back(unit8);
        GroundControl unit9;
        planSheet.push_back(unit9);
        Hopper unit10;
        planSheet.push_back(unit10);
        Hoverall unit11;
        planSheet.push_back(unit11);
        Interceptor unit12;
        planSheet.push_back(unit12);
        JetAmbulance unit13;
        planSheet.push_back(unit13);
        JetCopterRaider unit14;
        planSheet.push_back(unit14);
        JetRaider unit15;
        planSheet.push_back(unit15);
        JumpJet unit16;
        planSheet.push_back(unit16);
        Minicopter unit17;
        planSheet.push_back(unit17);
        MiniJetRaider unit18;
        planSheet.push_back(unit18);
        RepairCrew unit19;
        planSheet.push_back(unit19);
        RescueJet unit20;
        planSheet.push_back(unit20);
        Shuttle unit21;
        planSheet.push_back(unit21);
        Skimmer unit22;
        planSheet.push_back(unit22);
        TurboJet unit23;
        planSheet.push_back(unit23);
        WingCopter unit24;
        planSheet.push_back(unit24);
        WingRaider unit25;
        planSheet.push_back(unit25);
    }
    else if(nameIn == "Auto") {
        inventory.push_back(1); //1
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1); //5
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(1); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
        AirHorn unit1;
        planSheet.push_back(unit1);
        ArmoredSled unit2;
        planSheet.push_back(unit2);
        Basher unit3;
        planSheet.push_back(unit3);
        BXP100 unit4;
        planSheet.push_back(unit4);
        BXP200 unit5;
        planSheet.push_back(unit5);
        Crane unit6;
        planSheet.push_back(unit6);
        Dozer unit7;
        planSheet.push_back(unit7);
        Dragster unit8;
        planSheet.push_back(unit8);
        Flatbed unit9;
        planSheet.push_back(unit9);
        Forklift unit10;
        planSheet.push_back(unit10);
        GoKart unit11;
        planSheet.push_back(unit11);
        HoverPod unit12;
        planSheet.push_back(unit12);
        HoverSport unit13;
        planSheet.push_back(unit13);
        HoverTruck unit14;
        planSheet.push_back(unit14);
        LaserBuggy unit15;
        planSheet.push_back(unit15);
        MultiStation unit16;
        planSheet.push_back(unit16);
        Pushabout unit17;
        planSheet.push_back(unit17);
        RocketRacer unit18;
        planSheet.push_back(unit18);
        Rollabout unit19;
        planSheet.push_back(unit19);
        Semi unit20;
        planSheet.push_back(unit20);
        Speedster unit21;
        planSheet.push_back(unit21);
        Spike unit22;
        planSheet.push_back(unit22);
        Toboggan unit23;
        planSheet.push_back(unit23);
    }
    else if(nameIn == "Robo") {
        inventory.push_back(0); //1
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(6);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //10
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(6);
        inventory.push_back(4); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1); //20
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //25
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
        AlphaBot unit1;
        planSheet.push_back(unit1);
        BlasterBot unit2;
        planSheet.push_back(unit2);
        BrainBot unit3;
        planSheet.push_back(unit3);
        ClawBot unit4;
        planSheet.push_back(unit4);
        Cyclops unit5;
        planSheet.push_back(unit5);
        DrRobot unit6;
        planSheet.push_back(unit6);
        ExtendoBot unit7;
        planSheet.push_back(unit7);
        Fixit unit8;
        planSheet.push_back(unit8);
        Gearhead unit9;
        planSheet.push_back(unit9);
        Grappler unit10;
        planSheet.push_back(unit10);
        JumpBot unit11;
        planSheet.push_back(unit11);
        K9RovR unit12;
        planSheet.push_back(unit12);
        KnightBot unit13;
        planSheet.push_back(unit13);
        Lancer unit14;
        planSheet.push_back(unit14);
        Lifter unit15;
        planSheet.push_back(unit15);
        Longshot unit16;
        planSheet.push_back(unit16);
        Microhopper unit17;
        planSheet.push_back(unit17);
        NiceBot unit18;
        planSheet.push_back(unit18);
        Patroller unit19;
        planSheet.push_back(unit19);
        PestBot unit20;
        planSheet.push_back(unit20);
        RollerBot unit21;
        planSheet.push_back(unit21);
        Sparks unit22;
        planSheet.push_back(unit22);
        TuffBot unit23;
        planSheet.push_back(unit23);
    }
    else if(nameIn == "Wild") {
        inventory.push_back(0); //1
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(4);
        inventory.push_back(3); //15
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(3);
        inventory.push_back(1); //25
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(6);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //43
        for(int i = 44; i < 77; ++i) {
            inventory.push_back(0);
        }
        Ant unit1;
        planSheet.push_back(unit1);
        BabyGiantSquid unit2;
        planSheet.push_back(unit2);
        BabyRattler unit3;
        planSheet.push_back(unit3);
        BarnOwl unit4;
        planSheet.push_back(unit4);
        Bullfrog unit5;
        planSheet.push_back(unit5);
        Chimp unit6;
        planSheet.push_back(unit6);
        Croc unit7;
        planSheet.push_back(unit7);
        Flea unit8;
        planSheet.push_back(unit8);
        Gorilla unit9;
        planSheet.push_back(unit9);
        Kanga unit10;
        planSheet.push_back(unit10);
        KingCrab unit11;
        planSheet.push_back(unit11);
        Ladybug unit12;
        planSheet.push_back(unit12);
        Mantis unit13;
        planSheet.push_back(unit13);
        Minnow unit14;
        planSheet.push_back(unit14);
        Moth unit15;
        planSheet.push_back(unit15);
        PoisonMushroom unit16;
        planSheet.push_back(unit16);
        Rattler unit17;
        planSheet.push_back(unit17);
        Scorpion unit18;
        planSheet.push_back(unit18);
        Spider unit19;
        planSheet.push_back(unit19);
        StingingAnt unit20;
        planSheet.push_back(unit20);
        Tadpole unit21;
        planSheet.push_back(unit21);
        Treefrog unit22;
        planSheet.push_back(unit22);
        Turtle unit23;
        planSheet.push_back(unit23);
    }
    else if(nameIn == "Dragon") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(3);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(6);
        inventory.push_back(3); //15
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2); //20
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(2); //45
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //50
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0); //55
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //60
        inventory.push_back(6);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0); //70
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
        CaveBeetle unit1;
        planSheet.push_back(unit1);
        Crawling unit2;
        planSheet.push_back(unit2);
        CuriousHatchling unit3;
        planSheet.push_back(unit3);
        DragonRunt unit4;
        planSheet.push_back(unit4);
        DragonSerpent unit5;
        planSheet.push_back(unit5);
        DragonSlug unit6;
        planSheet.push_back(unit6);
        FireCritter unit7;
        planSheet.push_back(unit7);
        FireDragon unit8;
        planSheet.push_back(unit8);
        FireTrap unit9;
        planSheet.push_back(unit9);
        LandDragon unit10;
        planSheet.push_back(unit10);
        LizardMan unit11;
        planSheet.push_back(unit11);
        Snakeling unit12;
        planSheet.push_back(unit12);
        StormDragon unit13;
        planSheet.push_back(unit13);
        ThunderDragon unit14;
        planSheet.push_back(unit14);
        Wyrm unit15;
        planSheet.push_back(unit15);
        YoungHatchling unit16;
        planSheet.push_back(unit16);
    }
    else if(nameIn == "Monster") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //10
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(4);
        inventory.push_back(4); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //45
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(4); //50
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0); //55
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //60
        inventory.push_back(3);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //65
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
        BigMouth unit1;
        planSheet.push_back(unit1);
        Bucky unit2;
        planSheet.push_back(unit2);
        CreepieCrawly unit3;
        planSheet.push_back(unit3);
        Dizzy unit4;
        planSheet.push_back(unit4);
        Eyeball unit5;
        planSheet.push_back(unit5);
        EyeBeamer unit6;
        planSheet.push_back(unit6);
        Eyestalk unit7;
        planSheet.push_back(unit7);
        Frightful unit8;
        planSheet.push_back(unit8);
        Gremlin unit9;
        planSheet.push_back(unit9);
        GremlinHotfoot unit10;
        planSheet.push_back(unit10);
        GremlinKing unit11;
        planSheet.push_back(unit11);
        GremlinPorter unit12;
        planSheet.push_back(unit12);
        Hoppy unit13;
        planSheet.push_back(unit13);
        HypnoThing unit14;
        planSheet.push_back(unit14);
        It unit15;
        planSheet.push_back(unit15);
        Jumpy unit16;
        planSheet.push_back(unit16);
        LittleOneEye unit17;
        planSheet.push_back(unit17);
        MonsterSurgeon unit18;
        planSheet.push_back(unit18);
        NurseScarem unit19;
        planSheet.push_back(unit19);
        Slither unit20;
        planSheet.push_back(unit20);
        Smiler unit21;
        planSheet.push_back(unit21);
    }
    else if(nameIn == "Arachno") {
        inventory.push_back(0); //1
        inventory.push_back(3);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //40
        inventory.push_back(8);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //45
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2); //50
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(2); //55
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(1); //60
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //75
        inventory.push_back(0); //76
        Biter unit1;
        planSheet.push_back(unit1);
        BlackWidow unit2;
        planSheet.push_back(unit2);
        Bugling unit3;
        planSheet.push_back(unit3);
        Cricket unit4;
        planSheet.push_back(unit4);
        GrandaddyLongLegs unit5;
        planSheet.push_back(unit5);
        Hatchling unit6;
        planSheet.push_back(unit6);
        Jumper unit7;
        planSheet.push_back(unit7);
        PoisonBug unit8;
        planSheet.push_back(unit8);
        Scuttler unit9;
        planSheet.push_back(unit9);
        SlingerHatchling unit10;
        planSheet.push_back(unit10);
        StickleBack unit11;
        planSheet.push_back(unit11);
        Stinger unit12;
        planSheet.push_back(unit12);
        Tickler unit13;
        planSheet.push_back(unit13);
        UncleLongLegs unit14;
        planSheet.push_back(unit14);
        VenemousNettler unit15;
        planSheet.push_back(unit15);
        WebFlinger unit16;
        planSheet.push_back(unit16);
        WolfSpider unit17;
        planSheet.push_back(unit17);
    }
    else if(nameIn == "Aqua") {
        inventory.push_back(1); //1
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //5
        inventory.push_back(2);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //10
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //15
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //20
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //25
        inventory.push_back(1);
        inventory.push_back(3);
        inventory.push_back(2);
        inventory.push_back(2);
        inventory.push_back(0); //30
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //35
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(0);
        inventory.push_back(0); //40
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2);
        inventory.push_back(0); //45
        inventory.push_back(5);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //50
        inventory.push_back(0);
        inventory.push_back(3);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(2); //55
        inventory.push_back(2);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(4);
        inventory.push_back(1); //60
        inventory.push_back(5);
        inventory.push_back(4);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //65
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0); //70
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(0);
        inventory.push_back(1);
        inventory.push_back(1); //75
        inventory.push_back(2); //76
        ElectricEel unit1;
        planSheet.push_back(unit1);
        Flounder unit2;
        planSheet.push_back(unit2);
        FlyingFish unit3;
        planSheet.push_back(unit3);
        GreatWhite unit4;
        planSheet.push_back(unit4);
        Guppy unit5;
        planSheet.push_back(unit5);
        Hammerhead unit6;
        planSheet.push_back(unit6);
        HermitCrab unit7;
        planSheet.push_back(unit7);
        LampreyEel unit8;
        planSheet.push_back(unit8);
        ManOWar unit9;
        planSheet.push_back(unit9);
        Piranha unit10;
        planSheet.push_back(unit10);
        Plankton unit11;
        planSheet.push_back(unit11);
        PoisonAnemone unit12;
        planSheet.push_back(unit12);
        Porpoise unit13;
        planSheet.push_back(unit13);
        SeaHorse unit14;
        planSheet.push_back(unit14);
        SeaSnail unit15;
        planSheet.push_back(unit15);
        SeaSlug unit16;
        planSheet.push_back(unit16);
        Shrimp unit17;
        planSheet.push_back(unit17);
        Stingray unit18;
        planSheet.push_back(unit18);
        SeaTortoise unit19;
        planSheet.push_back(unit19);
    }
}

const std::string Pod::getName() const {
    return factionName;
}

const void Pod::printInventory() const {
    for(int i = 0; i < (int)inventory.size(); ++i) {
        std::cout << inventory.at(i) << ", ";
    }
    std::cout << "\n";
}

std::vector<int> Pod::getInventory() const {
    return inventory;
}

void Pod::addBrick(const int brickIndex) {
    ++inventory.at(brickIndex);
}

void Pod::removeBrick(const int brickIndex) {
    assert(inventory.at(brickIndex) > 0);
    --inventory.at(brickIndex);
}

void Pod::removeBrickSpecial(const int brickIndex) {
    --inventory.at(brickIndex);
}

const std::vector<Unit> Pod::getPlanSheet() const {
    return planSheet;
}

const Unit* Pod::getPlanSheetUnit(const int index) const {
    return &planSheet.at(index);
}
