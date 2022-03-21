//
// Created by minhtri on 21/03/2022.
//

#include "CreatureBuilder.h"
#include "../lib/random_selection.cpp"


std::unique_ptr<Creature> CreatureBuilder::make(int creatureID) {
    builder.reset();
    builder.initID(next_++);
    builder.initAccessories();
    builder.initSensors();
    builder.initBehaviour();
    builder.initPosition();
    builder.initPosition();
    builder.initVitesse();
    return builder.getResult();
}

RandomBuilder::RandomBuilder(CreatureBuilder &t_director, double t_eyeProb, double t_earProb, double t_shellProb, double t_camoProb,
                             double t_finProb, std::array<double, 4> t_behaviourDistrib): director(t_director) ,m_creature(&director.milieu) {
    m_eyeProb = t_eyeProb;
    m_earProb = t_earProb;
    m_shellProb = t_shellProb;
    m_camoProb = t_camoProb;
    m_finProb = t_finProb;

    m_behaviourDistrib = t_behaviourDistrib;
    //  Normalize the distrib ( just case)
    normalizeDistrib();

}

RandomBuilder::RandomBuilder(CreatureBuilder &t_director):director(t_director), m_creature(&director.milieu) {

}

void RandomBuilder::initID(int t_id) {
    m_creature.id = t_id;

}

void RandomBuilder::initAccessories() {
    // draw accessory type
    std::random_device rd;
    std::mt19937 mt(rd());
    // Shell
    std::bernoulli_distribution hasShell (m_shellProb);
    if (hasShell(mt)){
        std::unique_ptr<InterfaceAccessory> shell = std::unique_ptr<InterfaceAccessory>(new Shell(randomShellSpeedCoef(),
                                                                                                  randomShellDeathCoef()));
        m_creature.accessories->add(shell);
    }
    // Camo
    std::bernoulli_distribution hasCamo (m_camoProb);
    if (hasCamo(mt)) {
        std::unique_ptr<InterfaceAccessory> camo = std::unique_ptr<InterfaceAccessory>(new Camo(randomCamoCoef()));
        m_creature.accessories->add(camo);
    }
    // Fins
    std::bernoulli_distribution hasFins (m_finProb);
    if (hasFins(mt)) {
        std::unique_ptr<InterfaceAccessory> fins = std::unique_ptr<InterfaceAccessory>(new Fins(randomSpeedCoefFins()));
        m_creature.accessories->add(fins);
    }

}

void RandomBuilder::initSensors() {

}

void RandomBuilder::initBehaviour() {

}

void RandomBuilder::initPosition() {
    m_creature.setPos(randomPosition());
}

void RandomBuilder::initVitesse() {
    m_creature.setSpeed(randomSpeed());
}

std::array<double,4> RandomBuilder::getCumDistrib() {
    std::array<double, 4> cumDistrib {0,0,0,0};
    double cumSum = 0;
    for (double & i : m_behaviourDistrib){
        cumSum+= i;
        i = cumSum;
    }
    return cumDistrib;
}

void RandomBuilder::normalizeDistrib() {
    int s = 0;
    for (auto nb: m_behaviourDistrib) {
        s+= nb;
    }
    for (double & i : m_behaviourDistrib) {
        i /= s;
    }
}

std::unique_ptr<Creature> RandomBuilder::getResult() {
    return std::unique_ptr<Creature>(new Creature(m_creature));
}

void RandomBuilder::reset() {
    m_creature = Creature(&director.milieu);
}

