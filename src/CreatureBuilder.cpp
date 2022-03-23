//
// Created by minhtri on 21/03/2022.
//

#include "CreatureBuilder.h"
#include "../lib/random_creatures.cpp"
#include  <algorithm>

std::unique_ptr<Creature> CreatureBuilder::make() {
    return builder->make_getResult(next_++);
}

RandomBuilder::RandomBuilder(CreatureBuilder &t_director, double t_eyeProb, double t_earProb, double t_shellProb,
                             double t_camoProb,
                             double t_finProb, std::array<double, 4> t_behaviourDistrib) : director(t_director),
                                                                                           m_creature(
                                                                                                   &director.milieu) {
    m_eyeProb = t_eyeProb;
    m_earProb = t_earProb;
    m_shellProb = t_shellProb;
    m_camoProb = t_camoProb;
    m_finProb = t_finProb;

    m_behaviourDistrib = t_behaviourDistrib;
    //  Normalize the distrib ( just case)
    normalizeDistrib();

}

RandomBuilder::RandomBuilder(CreatureBuilder &t_director) : director(t_director), m_creature(&director.milieu) {

}

void RandomBuilder::initID(int t_id) {
    m_creature.id = t_id;

}

void RandomBuilder::initAccessories() {
    // draw accessory type
    std::random_device rd;
    std::mt19937 mt(rd());
    // Shell
    std::bernoulli_distribution hasShell(m_shellProb);
    if (hasShell(mt)) {
        std::unique_ptr<InterfaceAccessory> shell = std::unique_ptr<InterfaceAccessory>(
                new Shell(randomShellSpeedCoef(),
                          randomShellDeathCoef()));
        m_creature.accessories->add(shell);
    }
    // Camo
    std::bernoulli_distribution hasCamo(m_camoProb);
    if (hasCamo(mt)) {
        std::unique_ptr<InterfaceAccessory> camo = std::unique_ptr<InterfaceAccessory>(new Camo(randomCamoCoef()));
        m_creature.accessories->add(camo);
    }
    // Fins
    std::bernoulli_distribution hasFins(m_finProb);
    if (hasFins(mt)) {
        std::unique_ptr<InterfaceAccessory> fins = std::unique_ptr<InterfaceAccessory>(new Fins(randomSpeedCoefFins()));
        m_creature.accessories->add(fins);
    }

}

void RandomBuilder::initSensors() {
    std::random_device rd;
    std::mt19937 mt(rd());
    // Eyes
    std::bernoulli_distribution hasEyes(m_eyeProb);
    if (hasEyes(mt)) {
        std::unique_ptr<InterfaceSensors> eyes = std::unique_ptr<InterfaceSensors>(
                new Eyes(randomDetectionCoefEyes(), randomRadiusEyes(), randomDetectionAngleEyes()));
        m_creature.sensors->add(eyes);
    }
    // Ears
    std::bernoulli_distribution hasEars(m_earProb);
    if (hasEars(mt)) {
        std::unique_ptr<InterfaceSensors> ears = std::unique_ptr<InterfaceSensors>(
                new Ears(randomDetectionCoefEars(), randomRadiusEars()));
        m_creature.sensors->add(ears);
    }
}

void RandomBuilder::initBehaviour() {
    std::array<double, 4> cumDistrib = getCumDistrib();
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<> behaviourType(0, 1);
    double const behaviour = behaviourType(mt);
    if (behaviour <= cumDistrib[0]) { // Gregarious
        m_creature.behaviour = std::unique_ptr<GregariousBehaviour>(new GregariousBehaviour());
    } else if (behaviour <= cumDistrib[1]) { // Fearful
        m_creature.behaviour = std::unique_ptr<FearfulBehaviour>(
                new FearfulBehaviour(randomMaxNeighboursFearful(), randomFleeingSpeed()));
    } else if (behaviour <= cumDistrib[2]) { // Kamikaze
        m_creature.behaviour = std::unique_ptr<KamikazeBehaviour>(new KamikazeBehaviour(randomSpeedKamikaze()));
    } else { // Multiple
        m_creature.behaviour = std::unique_ptr<MultipleBehaviours>(new MultipleBehaviours());
        // populate the multiple behaviours
        std::array<int, 3> behaviours{0, 1, 2};
        int nbSelectedBehaviours = std::uniform_int_distribution<>(2, 10)(mt);
        std::vector<int> selectedBehaviours{};
        for (int i = 0; i < nbSelectedBehaviours; ++i) {
            int newBehaviour = getRandomIntDistrib(0, behaviours.size())(mt);
            if (newBehaviour == 1) { // Gregarious
                std::unique_ptr<InterfaceBehaviour> b = std::unique_ptr<GregariousBehaviour>(new GregariousBehaviour());
                dynamic_cast<MultipleBehaviours *>(m_creature.behaviour.get())
                        ->add(b);
            } else if (newBehaviour == 2) { // Fearful
                std::unique_ptr<InterfaceBehaviour> b = std::unique_ptr<FearfulBehaviour>
                        (new FearfulBehaviour(randomMaxNeighboursFearful(),
                                              randomFleeingSpeed()));
                dynamic_cast<MultipleBehaviours *>(m_creature.behaviour.get())
                        ->add(b);
            } else if (newBehaviour == 3) {
                std::unique_ptr<InterfaceBehaviour> b = std::unique_ptr<KamikazeBehaviour>
                        (new KamikazeBehaviour(randomSpeedKamikaze()));
                dynamic_cast<MultipleBehaviours *>(m_creature.behaviour.get())
                        ->add(b);
            }
        }
    }

}

void RandomBuilder::initPosition() {
    m_creature.setPos(randomPosition());
}

void RandomBuilder::initVitesse() {
    m_creature.setSpeed(randomSpeed());
    m_creature.previous_speed = m_creature.getSpeed();
    m_creature.setBaseSpeed(randomBaseSpeed());
}

void RandomBuilder::initLifetimeDuration() {
    m_creature.setDyingAge(randomDyingAge());
}

void RandomBuilder::initCreatureSize() {
    m_creature.setSize(randomCreatureSize());
}

std::array<double, 4> RandomBuilder::getCumDistrib() {
    std::array<double, 4> cumDistrib{0, 0, 0, 0};
    double cumSum = 0;
    for (double &i: m_behaviourDistrib) {
        cumSum += i;
        i = cumSum;
    }
    return cumDistrib;
}

void RandomBuilder::normalizeDistrib() {
    int s = 0;
    for (auto nb: m_behaviourDistrib) {
        s += nb;
    }
    for (double &i: m_behaviourDistrib) {
        i /= s;

    }
}

std::unique_ptr<Creature> RandomBuilder::getResult() {
    return std::unique_ptr<Creature>(new Creature(m_creature));
}

void RandomBuilder::reset() {
    m_creature = Creature(&director.milieu);
}

