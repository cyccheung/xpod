#include "Player.h"

const bool Player::enoughBricks(const Unit &unit) {
    //Use up bricks as if there are enough
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        pod.removeBrickSpecial(unit.getBricks().at(i));
    }
    //Loops through inventory to look for negative numbers, if found, not enough bricks
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        if(pod.getInventory().at(unit.getBricks().at(i)) < 0) {
            //Add bricks back into inventory before returning
            for(int j = 0; j < (int)unit.getBricks().size(); ++j) {
                pod.addBrick(unit.getBricks().at(j));
            }
            return false;
        }
    }
    //Add bricks back into inventory before returning
    for(int j = 0; j < (int)unit.getBricks().size(); ++j) {
        pod.addBrick(unit.getBricks().at(j));
    }
    //Otherwise return true
    return true;
}

const bool Player::enoughBricksRepair(const Unit &unit, const int repairedLevel) {
    //Use up bricks as if there are enough
    for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
        pod.removeBrickSpecial(unit.getBricks().at(i));
    }
    //Loops through inventory to look for negative numbers, if found, not enough bricks
    for(int i = 0; i < (int)unit.getBricks().size(); ++i) {
        if(pod.getInventory().at(unit.getBricks().at(i)) < 0) {
            //Add bricks back into inventory before returning
            for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
                pod.addBrick(unit.getBricks().at(i));
            }
            return false;
        }
    }
    //Add bricks back into inventory before returning
    for(int i = unit.getLevelBricks(repairedLevel - 1); i < unit.getLevelBricks(repairedLevel); ++i) {
        pod.addBrick(unit.getBricks().at(i));
    }
    //Otherwise return true
    return true;
}

Pod* Player::getPod() {
    return &pod;
}

const std::string Player::getName() const {
    return name;
}

void Player::buildUnit(const int index) {
    if(pod.getName() == "Aero") {
        if(index == 0) {
            AirCab* aircab = new AirCab;
            inactiveUnits.push_back(aircab);
        }
        else if(index == 1) {
            AirScout* airscout = new AirScout;
            inactiveUnits.push_back(airscout);
        }
        else if(index == 2) {
            CargoCopter* cargocopter = new CargoCopter;
            inactiveUnits.push_back(cargocopter);
        }
        else if(index == 3) {
            CopterRaider* copterraider = new CopterRaider;
            inactiveUnits.push_back(copterraider);
        }
        else if(index == 4) {
            DefenseStation* defensestation = new DefenseStation;
            inactiveUnits.push_back(defensestation);
        }
        else if(index == 5) {
            Flit* flit = new Flit;
            inactiveUnits.push_back(flit);
        }
        else if(index == 6) {
            GliderMedic* glidermedic = new GliderMedic;
            inactiveUnits.push_back(glidermedic);
        }
        else if(index == 7) {
            GroundMedic* groundmedic = new GroundMedic;
            inactiveUnits.push_back(groundmedic);
        }
        else if(index == 8) {
            GroundControl* groundcontrol = new GroundControl;
            inactiveUnits.push_back(groundcontrol);
        }
        else if(index == 9) {
            Hopper* hopper = new Hopper;
            inactiveUnits.push_back(hopper);
        }
        else if(index == 10) {
            Hoverall* hoverall = new Hoverall;
            inactiveUnits.push_back(hoverall);
        }
        else if(index == 11) {
            Interceptor* interceptor = new Interceptor;
            inactiveUnits.push_back(interceptor);
        }
        else if(index == 12) {
            JetAmbulance* jetambulance = new JetAmbulance;
            inactiveUnits.push_back(jetambulance);
        }
        else if(index == 13) {
            JetCopterRaider* jetcopterraider = new JetCopterRaider;
            inactiveUnits.push_back(jetcopterraider);
        }
        else if(index == 14) {
            JetRaider* jetraider = new JetRaider;
            inactiveUnits.push_back(jetraider);
        }
        else if(index == 15) {
            JumpJet* jumpjet = new JumpJet;
            inactiveUnits.push_back(jumpjet);
        }
        else if(index == 16) {
            Minicopter* minicopter = new Minicopter;
            inactiveUnits.push_back(minicopter);
        }
        else if(index == 17) {
            MiniJetRaider* minijetraider = new MiniJetRaider;
            inactiveUnits.push_back(minijetraider);
        }
        else if(index == 18) {
            RepairCrew* repaircrew = new RepairCrew;
            inactiveUnits.push_back(repaircrew);
        }
        else if(index == 19) {
            RescueJet* rescuejet = new RescueJet;
            inactiveUnits.push_back(rescuejet);
        }
        else if(index == 20) {
            Shuttle* shuttle = new Shuttle;
            inactiveUnits.push_back(shuttle);
        }
        else if(index == 21) {
            Skimmer* skimmer = new Skimmer;
            inactiveUnits.push_back(skimmer);
        }
        else if(index == 22) {
            TurboJet* turbojet = new TurboJet;
            inactiveUnits.push_back(turbojet);
        }
        else if(index == 23) {
            WingCopter* wingcopter = new WingCopter;
            inactiveUnits.push_back(wingcopter);
        }
        else if(index == 24) {
            WingRaider* wingraider = new WingRaider;
            inactiveUnits.push_back(wingraider);
        }
    }
    else if(pod.getName() == "Auto") {
        if(index == 0) {
            AirHorn* airhorn = new AirHorn;
            inactiveUnits.push_back(airhorn);
        }
        else if(index == 1) {
            ArmoredSled* armoredsled = new ArmoredSled;
            inactiveUnits.push_back(armoredsled);
        }
        else if(index == 2) {
            Basher* basher = new Basher;
            inactiveUnits.push_back(basher);
        }
        else if(index == 3) {
            BXP100* bxp100 = new BXP100;
            inactiveUnits.push_back(bxp100);
        }
        else if(index == 4) {
            BXP200* bxp200 = new BXP200;
            inactiveUnits.push_back(bxp200);
        }
        else if(index == 5) {
            Crane* crane = new Crane;
            inactiveUnits.push_back(crane);
        }
        else if(index == 6) {
            Dozer* dozer = new Dozer;
            inactiveUnits.push_back(dozer);
        }
        else if(index == 7) {
            Dragster* dragster = new Dragster;
            inactiveUnits.push_back(dragster);
        }
        else if(index == 8) {
            Flatbed* flatbed = new Flatbed;
            inactiveUnits.push_back(flatbed);
        }
        else if(index == 9) {
            Forklift* forklift = new Forklift;
            inactiveUnits.push_back(forklift);
        }
        else if(index == 10) {
            GoKart* gokart = new GoKart;
            inactiveUnits.push_back(gokart);
        }
        else if(index == 11) {
            HoverPod* hoverpod = new HoverPod;
            inactiveUnits.push_back(hoverpod);
        }
        else if(index == 12) {
            HoverSport* hoversport = new HoverSport;
            inactiveUnits.push_back(hoversport);
        }
        else if(index == 13) {
            HoverTruck* hovertruck = new HoverTruck;
            inactiveUnits.push_back(hovertruck);
        }
        else if(index == 14) {
            LaserBuggy* laserbuggy = new LaserBuggy;
            inactiveUnits.push_back(laserbuggy);
        }
        else if(index == 15) {
            MultiStation* multistation = new MultiStation;
            inactiveUnits.push_back(multistation);
        }
        else if(index == 16) {
            Pushabout* pushabout = new Pushabout;
            inactiveUnits.push_back(pushabout);
        }
        else if(index == 17) {
            RocketRacer* rocketracer = new RocketRacer;
            inactiveUnits.push_back(rocketracer);
        }
        else if(index == 18) {
            Rollabout* rollabout = new Rollabout;
            inactiveUnits.push_back(rollabout);
        }
        else if(index == 19) {
            Semi* semi = new Semi;
            inactiveUnits.push_back(semi);
        }
        else if(index == 20) {
            Speedster* speedster = new Speedster;
            inactiveUnits.push_back(speedster);
        }
        else if(index == 21) {
            Spike* spike = new Spike;
            inactiveUnits.push_back(spike);
        }
        else if(index == 22) {
            Toboggan* toboggan = new Toboggan;
            inactiveUnits.push_back(toboggan);
        }
    }
    else if(pod.getName() == "Robo") {
        if(index == 0) {
            AlphaBot* alphaBot = new AlphaBot;
            inactiveUnits.push_back(alphaBot);
        }
        else if(index == 1) {
            BlasterBot* blasterbot = new BlasterBot;
            inactiveUnits.push_back(blasterbot);
        }
        else if(index == 2) {
            BrainBot* brainbot = new BrainBot;
            inactiveUnits.push_back(brainbot);
        }
        else if(index == 3) {
            ClawBot* clawbot = new ClawBot;
            inactiveUnits.push_back(clawbot);
        }
        else if(index == 4) {
            Cyclops* cyclops = new Cyclops;
            inactiveUnits.push_back(cyclops);
        }
        else if(index == 5) {
            DrRobot* drrobot = new DrRobot;
            inactiveUnits.push_back(drrobot);
        }
        else if(index == 6) {
            ExtendoBot* extendobot = new ExtendoBot;
            inactiveUnits.push_back(extendobot);
        }
        else if(index == 7) {
            Fixit* fixit = new Fixit;
            inactiveUnits.push_back(fixit);
        }
        else if(index == 8) {
            Gearhead* gearhead = new Gearhead;
            inactiveUnits.push_back(gearhead);
        }
        else if(index == 9) {
            Grappler* grappler = new Grappler;
            inactiveUnits.push_back(grappler);
        }
        else if(index == 10) {
            JumpBot* jumpbot = new JumpBot;
            inactiveUnits.push_back(jumpbot);
        }
        else if(index == 11) {
            K9RovR* k9rovr = new K9RovR;
            inactiveUnits.push_back(k9rovr);
        }
        else if(index == 12) {
            KnightBot* knightbot = new KnightBot;
            inactiveUnits.push_back(knightbot);
        }
        else if(index == 13) {
            Lancer* lancer = new Lancer;
            inactiveUnits.push_back(lancer);
        }
        else if(index == 14) {
            Lifter* lifter = new Lifter;
            inactiveUnits.push_back(lifter);
        }
        else if(index == 15) {
            Longshot* longshot = new Longshot;
            inactiveUnits.push_back(longshot);
        }
        else if(index == 16) {
            Microhopper* microhopper = new Microhopper;
            inactiveUnits.push_back(microhopper);
        }
        else if(index == 17) {
            NiceBot* nicebot = new NiceBot;
            inactiveUnits.push_back(nicebot);
        }
        else if(index == 18) {
            Patroller* patroller = new Patroller;
            inactiveUnits.push_back(patroller);
        }
        else if(index == 19) {
            PestBot* pestbot = new PestBot;
            inactiveUnits.push_back(pestbot);
        }
        else if(index == 20) {
            RollerBot* rollerbot = new RollerBot;
            inactiveUnits.push_back(rollerbot);
        }
        else if(index == 21) {
            Sparks* sparks = new Sparks;
            inactiveUnits.push_back(sparks);
        }
        else if(index == 22) {
            TuffBot* tuffbot = new TuffBot;
            inactiveUnits.push_back(tuffbot);
        }
    }
    else if(pod.getName() == "Wild") {
        if(index == 0) {
            Ant* ant = new Ant;
            inactiveUnits.push_back(ant);
        }
        else if(index == 1) {
            BabyGiantSquid* babygiantsquid = new BabyGiantSquid;
            inactiveUnits.push_back(babygiantsquid);
        }
        else if(index == 2) {
            BabyRattler* babyrattler = new BabyRattler;
            inactiveUnits.push_back(babyrattler);
        }
        else if(index == 3) {
            BarnOwl* barnowl = new BarnOwl;
            inactiveUnits.push_back(barnowl);
        }
        else if(index == 4) {
            Bullfrog* bullfrog = new Bullfrog;
            inactiveUnits.push_back(bullfrog);
        }
        else if(index == 5) {
            Chimp* chimp = new Chimp;
            inactiveUnits.push_back(chimp);
        }
        else if(index == 6) {
            Croc* croc = new Croc;
            inactiveUnits.push_back(croc);
        }
        else if(index == 7) {
            Flea* flea = new Flea;
            inactiveUnits.push_back(flea);
        }
        else if(index == 8) {
            Gorilla* gorilla = new Gorilla;
            inactiveUnits.push_back(gorilla);
        }
        else if(index == 9) {
            Kanga* kanga = new Kanga;
            inactiveUnits.push_back(kanga);
        }
        else if(index == 10) {
            KingCrab* kingcrab = new KingCrab;
            inactiveUnits.push_back(kingcrab);
        }
        else if(index == 11) {
            Ladybug* ladybug = new Ladybug;
            inactiveUnits.push_back(ladybug);
        }
        else if(index == 12) {
            Mantis* mantis = new Mantis;
            inactiveUnits.push_back(mantis);
        }
        else if(index == 13) {
            Minnow* minnow = new Minnow;
            inactiveUnits.push_back(minnow);
        }
        else if(index == 14) {
            Moth* moth = new Moth;
            inactiveUnits.push_back(moth);
        }
        else if(index == 15) {
            PoisonMushroom* poisonmushroom = new PoisonMushroom;
            inactiveUnits.push_back(poisonmushroom);
        }
        else if(index == 16) {
            Rattler* rattler = new Rattler;
            inactiveUnits.push_back(rattler);
        }
        else if(index == 17) {
            Scorpion* scorpion = new Scorpion;
            inactiveUnits.push_back(scorpion);
        }
        else if(index == 18) {
            Spider* spider = new Spider;
            inactiveUnits.push_back(spider);
        }
        else if(index == 19) {
            StingingAnt* stingingant = new StingingAnt;
            inactiveUnits.push_back(stingingant);
        }
        else if(index == 20) {
            Tadpole* tadpole = new Tadpole;
            inactiveUnits.push_back(tadpole);
        }
        else if(index == 21) {
            Treefrog* treefrog = new Treefrog;
            inactiveUnits.push_back(treefrog);
        }
        else if(index == 22) {
            Turtle* turtle = new Turtle;
            inactiveUnits.push_back(turtle);
        }
    }
    else if(pod.getName() == "Dragon") {
        if(index == 0) {
            CaveBeetle* cavebeetle = new CaveBeetle;
            inactiveUnits.push_back(cavebeetle);
        }
        else if(index == 1) {
            Crawling* crawling = new Crawling;
            inactiveUnits.push_back(crawling);
        }
        else if(index == 2) {
            CuriousHatchling* curioushatchling = new CuriousHatchling;
            inactiveUnits.push_back(curioushatchling);
        }
        else if(index == 3) {
            DragonRunt* dragonrunt = new DragonRunt;
            inactiveUnits.push_back(dragonrunt);
        }
        else if(index == 4) {
            DragonSerpent* dragonserpent = new DragonSerpent;
            inactiveUnits.push_back(dragonserpent);
        }
        else if(index == 5) {
            DragonSlug* dragonslug = new DragonSlug;
            inactiveUnits.push_back(dragonslug);
        }
        else if(index == 6) {
            FireCritter* firecritter = new FireCritter;
            inactiveUnits.push_back(firecritter);
        }
        else if(index == 7) {
            FireDragon* firedragon = new FireDragon;
            inactiveUnits.push_back(firedragon);
        }
        else if(index == 8) {
            FireTrap* firetrap = new FireTrap;
            inactiveUnits.push_back(firetrap);
        }
        else if(index == 9) {
            LandDragon* landdragon = new LandDragon;
            inactiveUnits.push_back(landdragon);
        }
        else if(index == 10) {
            LizardMan* lizardman = new LizardMan;
            inactiveUnits.push_back(lizardman);
        }
        else if(index == 11) {
            Snakeling* snakeling = new Snakeling;
            inactiveUnits.push_back(snakeling);
        }
        else if(index == 12) {
            StormDragon* stormdragon = new StormDragon;
            inactiveUnits.push_back(stormdragon);
        }
        else if(index == 13) {
            ThunderDragon* thunderdragon = new ThunderDragon;
            inactiveUnits.push_back(thunderdragon);
        }
        else if(index == 14) {
            Wyrm* wyrm = new Wyrm;
            inactiveUnits.push_back(wyrm);
        }
        else if(index == 15) {
            YoungHatchling* younghatchling = new YoungHatchling;
            inactiveUnits.push_back(younghatchling);
        }
    }
    else if(pod.getName() == "Monster") {
        if(index == 0) {
            BigMouth* bigmouth = new BigMouth;
            inactiveUnits.push_back(bigmouth);
        }
        else if(index == 1) {
            Bucky* bucky = new Bucky;
            inactiveUnits.push_back(bucky);
        }
        else if(index == 2) {
            CreepieCrawly* creepiecrawly = new CreepieCrawly;
            inactiveUnits.push_back(creepiecrawly);
        }
        else if(index == 3) {
            Dizzy* dizzy = new Dizzy;
            inactiveUnits.push_back(dizzy);
        }
        else if(index == 4) {
            Eyeball* eyeball = new Eyeball;
            inactiveUnits.push_back(eyeball);
        }
        else if(index == 5) {
            EyeBeamer* eyebeamer = new EyeBeamer;
            inactiveUnits.push_back(eyebeamer);
        }
        else if(index == 6) {
            Eyestalk* eyestalk = new Eyestalk;
            inactiveUnits.push_back(eyestalk);
        }
        else if(index == 7) {
            Frightful* frightful = new Frightful;
            inactiveUnits.push_back(frightful);
        }
        else if(index == 8) {
            Gremlin* gremlin = new Gremlin;
            inactiveUnits.push_back(gremlin);
        }
        else if(index == 9) {
            GremlinHotfoot* gremlinhotfoot = new GremlinHotfoot;
            inactiveUnits.push_back(gremlinhotfoot);
        }
        else if(index == 10) {
            GremlinKing* gremlinking = new GremlinKing;
            inactiveUnits.push_back(gremlinking);
        }
        else if(index == 11) {
            GremlinPorter* gremlinporter = new GremlinPorter;
            inactiveUnits.push_back(gremlinporter);
        }
        else if(index == 12) {
            Hoppy* hoppy = new Hoppy;
            inactiveUnits.push_back(hoppy);
        }
        else if(index == 13) {
            HypnoThing* hypnothing = new HypnoThing;
            inactiveUnits.push_back(hypnothing);
        }
        else if(index == 14) {
            It* it = new It;
            inactiveUnits.push_back(it);
        }
        else if(index == 15) {
            Jumpy* jumpy = new Jumpy;
            inactiveUnits.push_back(jumpy);
        }
        else if(index == 16) {
            LittleOneEye* littleoneeye = new LittleOneEye;
            inactiveUnits.push_back(littleoneeye);
        }
        else if(index == 17) {
            MonsterSurgeon* monstersurgeon = new MonsterSurgeon;
            inactiveUnits.push_back(monstersurgeon);
        }
        else if(index == 18) {
            NurseScarem* nursescarem = new NurseScarem;
            inactiveUnits.push_back(nursescarem);
        }
        else if(index == 19) {
            Slither* slither = new Slither;
            inactiveUnits.push_back(slither);
        }
        else if(index == 20) {
            Smiler* smiler = new Smiler;
            inactiveUnits.push_back(smiler);
        }
    }
    else if(pod.getName() == "Arachno") {
        if(index == 0) {
            Biter* biter = new Biter;
            inactiveUnits.push_back(biter);
        }
        else if(index == 1) {
            BlackWidow* blackwidow = new BlackWidow;
            inactiveUnits.push_back(blackwidow);
        }
        else if(index == 2) {
            Bugling* bugling = new Bugling;
            inactiveUnits.push_back(bugling);
        }
        else if(index == 3) {
            Cricket* cricket = new Cricket;
            inactiveUnits.push_back(cricket);
        }
        else if(index == 4) {
            GrandaddyLongLegs* grandaddylonglegs = new GrandaddyLongLegs;
            inactiveUnits.push_back(grandaddylonglegs);
        }
        else if(index == 5) {
            Hatchling* hatchling = new Hatchling;
            inactiveUnits.push_back(hatchling);
        }
        else if(index == 6) {
            Jumper* jumper = new Jumper;
            inactiveUnits.push_back(jumper);
        }
        else if(index == 7) {
            PoisonBug* poisonbug = new PoisonBug;
            inactiveUnits.push_back(poisonbug);
        }
        else if(index == 8) {
            Scuttler* scuttler = new Scuttler;
            inactiveUnits.push_back(scuttler);
        }
        else if(index == 9) {
            SlingerHatchling* slingerhatchling = new SlingerHatchling;
            inactiveUnits.push_back(slingerhatchling);
        }
        else if(index == 10) {
            StickleBack* stickleback = new StickleBack;
            inactiveUnits.push_back(stickleback);
        }
        else if(index == 11) {
            Stinger* stinger = new Stinger;
            inactiveUnits.push_back(stinger);
        }
        else if(index == 12) {
            Tickler* tickler = new Tickler;
            inactiveUnits.push_back(tickler);
        }
        else if(index == 13) {
            UncleLongLegs* unclelonglegs = new UncleLongLegs;
            inactiveUnits.push_back(unclelonglegs);
        }
        else if(index == 14) {
            VenemousNettler* venemousnettler = new VenemousNettler;
            inactiveUnits.push_back(venemousnettler);
        }
        else if(index == 15) {
            WebFlinger* webflinger = new WebFlinger;
            inactiveUnits.push_back(webflinger);
        }
        else if(index == 16) {
            WolfSpider* wolfspider = new WolfSpider;
            inactiveUnits.push_back(wolfspider);
        }
    }
    else if(pod.getName() == "Aqua") {
        if(index == 0) {
            ElectricEel* electriceel = new ElectricEel;
            inactiveUnits.push_back(electriceel);
        }
        else if(index == 1) {
            Flounder* flounder = new Flounder;
            inactiveUnits.push_back(flounder);
        }
        else if(index == 2) {
            FlyingFish* flyingfish = new FlyingFish;
            inactiveUnits.push_back(flyingfish);
        }
        else if(index == 3) {
            GreatWhite* greatwhite = new GreatWhite;
            inactiveUnits.push_back(greatwhite);
        }
        else if(index == 4) {
            Guppy* guppy = new Guppy;
            inactiveUnits.push_back(guppy);
        }
        else if(index == 5) {
            Hammerhead* hammerhead = new Hammerhead;
            inactiveUnits.push_back(hammerhead);
        }
        else if(index == 6) {
            HermitCrab* hermitcrab = new HermitCrab;
            inactiveUnits.push_back(hermitcrab);
        }
        else if(index == 7) {
            LampreyEel* lampreyeel = new LampreyEel;
            inactiveUnits.push_back(lampreyeel);
        }
        else if(index == 8) {
            ManOWar* manowar = new ManOWar;
            inactiveUnits.push_back(manowar);
        }
        else if(index == 9) {
            Piranha* piranha = new Piranha;
            inactiveUnits.push_back(piranha);
        }
        else if(index == 10) {
            Plankton* plankton = new Plankton;
            inactiveUnits.push_back(plankton);
        }
        else if(index == 11) {
            PoisonAnemone* poisonanemone = new PoisonAnemone;
            inactiveUnits.push_back(poisonanemone);
        }
        else if(index == 12) {
            Porpoise* porpoise = new Porpoise;
            inactiveUnits.push_back(porpoise);
        }
        else if(index == 13) {
            SeaHorse* seahorse = new SeaHorse;
            inactiveUnits.push_back(seahorse);
        }
        else if(index == 14) {
            SeaSnail* seasnail = new SeaSnail;
            inactiveUnits.push_back(seasnail);
        }
        else if(index == 15) {
            SeaSlug* seaslug = new SeaSlug;
            inactiveUnits.push_back(seaslug);
        }
        else if(index == 16) {
            Shrimp* shrimp = new Shrimp;
            inactiveUnits.push_back(shrimp);
        }
        else if(index == 17) {
            Stingray* stingray = new Stingray;
            inactiveUnits.push_back(stingray);
        }
        else if(index == 18) {
            SeaTortoise* seatortoise = new SeaTortoise;
            inactiveUnits.push_back(seatortoise);
        }
    }
    //Use up bricks by getting the last unit in inactiveUnits vector and using bricks
    useBricks(inactiveUnits.at(inactiveUnits.size() - 1));
}

void Player::activateUnit(Unit* unitPtr) {
    //Adds unit to active units vector
    units.push_back(unitPtr);
    //Finds unit's index
    int index = findInactiveUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeInactiveUnit(Unit* unitPtr) {
    //Finds unit's index
    int index = findInactiveUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        //Returns unit's bricks to inventory
        returnBricks(unitPtr);
        delete inactiveUnits.at(index);
        //Removes unit from inactive units vector
        inactiveUnits.erase(inactiveUnits.begin() + index);
    }
}

void Player::removeUnit(Unit* unitPtr) {
    //Finds unit's index
    int index = findUnit(unitPtr);
    //Remove unit from units vector if found, otherwise do nothing
    if(index >= 0) {
        for(int i = 0; i < unitPtr->getLevel(); ++i) {
            //Returns unit's bricks to inventory
            returnBricks(unitPtr);
            //Lower's unit's level by one
            unitPtr->setLevel(unitPtr->getLevel() - 1);
        }
        delete units.at(index);
        //Removes unit from units vector
        units.erase(units.begin() + index);
    }
}

void Player::useBricks(Unit* unitPtr) {
    for(int i = 0; i < (int)unitPtr->getBricks().size(); ++i) {
        pod.removeBrick(unitPtr->getBricks().at(i));
    }
}

void Player::useBricks(Unit* unitPtr, const int levels) {
    for(int i = unitPtr->getLevelBricks(unitPtr->getLevel()); i < unitPtr->getLevelBricks(unitPtr->getLevel() + levels); ++i) {
        pod.removeBrick(unitPtr->getBricks().at(i));
    }
}

void Player::returnBricks(Unit* unitPtr) {
    std::vector<int> tempBricks;
    for(int i = unitPtr->getLevelBricks(unitPtr->getLevel() - 1); i < unitPtr->getLevelBricks(unitPtr->getLevel()); ++i) {
        tempBricks.push_back(unitPtr->getBricks().at(i));
    }
    for(int i = 0; i < (int)tempBricks.size(); ++i) {
        pod.addBrick(tempBricks.at(i));
    }
}

std::vector<Unit*> Player::getUnits() const {
    return units;
}

Unit* Player::getUnit(const int index) {
    return units.at(index);
}

void Player::printActive() const {
    std::cout << "Active units:\n";
    for(int i = 0; i < (int)units.size(); ++i) {
        std::cout << "[" << i << "]\n";
        units.at(i)->printInfo();
    }
}

void Player::printInactive() const {
    std::cout << "Inactive units:\n";
    for(int i = 0; i < (int)inactiveUnits.size(); ++i) {
        std::cout << "[" << i << "]\n";
        inactiveUnits.at(i)->printAbilities();
    }
}

void Player::addUnit(Unit* unitPtr) {
    units.push_back(unitPtr);
}

std::vector<Unit*> Player::getInactiveUnits() const {
    return inactiveUnits;
}

Unit* Player::getInactiveUnit(const int index) {
    return inactiveUnits.at(index);
}

void Player::addInactiveUnit(Unit* unitPtr) {
    inactiveUnits.push_back(unitPtr);
}

int Player::findInactiveUnit(Unit* unitPtr) {
    for(int i = 0; i < (int)inactiveUnits.size(); ++i) {
        if(unitPtr == inactiveUnits.at(i)) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}

int Player::findUnit(Unit* unitPtr) {
    for(int i = 0; i < (int)units.size(); ++i) {
        if(unitPtr == units.at(i)) {
            return i;
        }
    }
    return -1;      //Return -1 if not found
}

const bool Player::duplicateUnits(Unit* unitPtr) {
    //If any of the other units have the same name, return true
    for(int i = 0; i < (int)units.size(); ++i) {
        //Makes sure to not check itself
        if(units.at(i)->getName() == unitPtr->getName() && units.at(i) != unitPtr) {
            return true;
        }
    }
    return false;
}

void Player::printPlanSheet() {
    for(int i = 0; i < (int)pod.getPlanSheet().size(); ++i) {
        //If not enough bricks to build, add a *
        if(!enoughBricks(pod.getPlanSheet().at(i))) {
            std::cout << "*";
        }
        std::cout << "[" << i << "] ";
        pod.getPlanSheet().at(i).printAbilities();
        std::cout << "\n";
    }
}

void Player::setActivePosition(const int choice, const std::pair<int,int> &position) {
    units.at(choice)->setPosition(position);
}

void Player::setInactivePosition(const int choice, const std::pair<int,int> &position) {
    inactiveUnits.at(choice)->setPosition(position);
}
