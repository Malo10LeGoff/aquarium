#include "Milieu.h"
#include "Sensors.h"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <iostream>
#include <fstream>
#include <random>
#include "constants.h"
const T Milieu::white[] = {(T) 255, (T) 255, (T) 255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3),
                                          width(_width), height(_height), builder(CreatureBuilder(*this)) {

    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu(void) {

    cout << "dest Milieu" << endl;
}

void Milieu::step(void) {
    cur_step+=1;

    // Detect surroundings
    creatureDetectSurroundings();
    // move creatures
    moveCreatures();
    // Calculate creature that have colided
    // TODO : calculate creatures that have collided
    // handle creature collisions
    handleCreatureCollision();
    // add 1 to creature ages
    ageCreature();
    cloneCreatures();
    // Kill creatures that need to die
    killCreatures();
    addCreatures();

    spawnCreatures();
    
    //draw
    draw();
    //writeData
    writeData(cur_step);
    
}


int Milieu::Milieu::getNbCreatures() {
    return listeCreatures.size();
}

std::vector<array<Vector, 2>> Milieu::surrounding(const Creature &a) {

    std::vector<array<Vector, 2>> res{};

    for (auto const &creature: listeCreatures)
        if ((a != *creature) && detect(a, *creature)) {

            Vector pos_tmp = creature->getPos();
            Vector speed = creature->getSpeed();
            array<Vector, 2> tmp_ar{speed, pos_tmp};
            res.push_back(tmp_ar);
        }
    return res;
};


bool Milieu::detect(const Creature &a, const Creature &b) {

    Vector pos_a = a.getPos();
    Vector pos_b = b.getPos();

    double alpha_2 = (pos_b - pos_a).orientation();
    if (alpha_2 > M_PI) {
        alpha_2 = std::abs(alpha_2 - 2 * M_PI);
    }
    double alpha_1 = a.getSpeed().orientation();
    double dist_a_b = distanceVectors(pos_a, pos_b);
    std::vector<detection_caract> detectionZones = a.sensors->getDetectionZone(); // [ [detectionCoef, detectionRadius, DetectionAngle], ...]
    for (auto const &detectionZone: detectionZones) {
        bool isCloseEnough = detectionZone[1] > dist_a_b;
        bool isInDetectionAngle = (detectionZone[2] / 2.0) > std::abs(alpha_2 - alpha_1);
        bool isDetectionStrongEnough  = detectionZone[0] > b.getCamoCoef();
        if (isCloseEnough && isInDetectionAngle && isDetectionStrongEnough ) {
            return true;
        }
    }


    return false;
}


void Milieu::handleCreatureCollision(void) {
    std::vector<int> tmp_vector{};
    for (auto &creature_i: listeCreatures) {
        for (auto &creature_j: listeCreatures) {
            if (creature_i->getId() != creature_j->getId()) {
                if (creature_j->getHitbox().isColliding(creature_i->getHitbox())) {
                    creature_i->onCreatureCollision();
                    //creature_j->onCreatureCollision();
                }
            }
        }
    }

}

void Milieu::addMember(std::unique_ptr<Creature> &b) {
    listeCreatures.push_back(std::move(b));
}

void Milieu::addRandomMember() {
    std::unique_ptr<Creature> randomCreature = builder.makeRandom();
    addMember(randomCreature);

}

void Milieu::moveCreatures() {
    for (auto &creature: listeCreatures) {
        creature->onMove(*this);
    }
}

void Milieu::creatureDetectSurroundings() {
    for (auto &creature: listeCreatures) {
        creature->detectSurroundings();
    }
}


void Milieu::addCreatureToKill(int i) {
    creaturesToKill.push_back(i);
}

void Milieu::EnvironmentKill() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::bernoulli_distribution shouldDie(1/ creatureKillRate);
    for (auto &creature: listeCreatures) {
        if (shouldDie(mt)) {
            creaturesToKill.push_back(creature->getId());
        }
    }
}

void Milieu::draw() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, 255, 255, 255);
    for (auto &creature: listeCreatures) {
        creature->draw(*this);
    }
}

void Milieu::killCreatures() {
    EnvironmentKill();
    for (auto id: creaturesToKill) {
        listeCreatures.erase(std::remove_if(
                listeCreatures.begin(), listeCreatures.end(),
                [id](decltype(listeCreatures)::value_type const &c) {
                    return c->getId() == id;
                }), listeCreatures.end());
    }
    creaturesToKill = std::vector<int>{};
}

void Milieu::ageCreature() {
    for (auto &creature: listeCreatures) {
        creature->onAge();
    }
}

void Milieu::spawnCreatures() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::bernoulli_distribution shouldSpawnCreature (1 / creatureSpawnRate);
    if (shouldSpawnCreature(mt)) {
        addRandomMember();
    }
 }

void Milieu::cloneCreatures() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::bernoulli_distribution shouldGetCloned (1 / creatureCloneRate);
    for (auto &creature : listeCreatures){
        if (shouldGetCloned(mt)) {
            cloneCreature(*creature);
        }
    }
}


void Milieu::writeData(int c_step) 
{
    ofstream myfile;
    myfile.open ("data.txt", std::ios::app);
    int pop[5] = {0,0,0,0,0};
    for (auto const &creature: listeCreatures) {
        char c = creature->getBehaviorType();
        if (c=='G') {pop[0]+=1;}
        if (c=='F') {pop[1]+=1;}
        if (c=='K') {pop[2]+=1;}
        if (c=='P') {pop[3]+=1;}
        if (c=='M') {pop[4]+=1;}
    }
    
    myfile << "Step " << c_step << ":" <<pop[0] << ","<<pop[1] << ","<<pop[2] << ","<<pop[3] << ","<<pop[4] << "," <<"/n" << endl;
    myfile.close();
}

void Milieu::cloneCreature(Creature &creature) {
    std::unique_ptr<Creature> cloneCreature = builder.makeClone(creature);
    creaturesToAdd.push_back(std::move(cloneCreature));
}

void Milieu::addCreatures() {
    for (auto &creatureToAdd : creaturesToAdd) {
        addMember(creatureToAdd);
    }
    creaturesToAdd = std::vector<std::unique_ptr<Creature>> {};
}
