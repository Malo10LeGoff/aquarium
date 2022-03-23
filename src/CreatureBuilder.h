//
// Created by minhtri on 21/03/2022.
//

#ifndef AQUARIUM_CREATUREBUILDER_H
#define AQUARIUM_CREATUREBUILDER_H

#include <memory>
#include "Creature.h"
#include "constants.h"

class CreatureBuilder;

class BuilderInterface {
public :
    virtual void initID(int id) = 0;

    virtual void initAccessories() = 0;

    virtual void initSensors() = 0;

    virtual void initBehaviour() = 0;

    virtual void initPosition() = 0;

    virtual void initVitesse() = 0;

    virtual void initCreatureSize() = 0;

    virtual void initLifetimeDuration() = 0;

    virtual std::unique_ptr<Creature> getResult() = 0;

    virtual std::unique_ptr<Creature> make_getResult(int id) {
        reset();
        initID(id);
        initCreatureSize();
        initLifetimeDuration();
        initAccessories();
        initSensors();
        initBehaviour();
        initPosition();
        initPosition();
        initVitesse();
        return getResult();
    };

    virtual void reset() = 0;
};

class RandomBuilder : public BuilderInterface {
public:
    /**
     * Creates a creature with a given probability distribution
     * @param t_director director the builder refers to
     * @param t_eyeProb the probability of having eyes
     * @param t_earProb the probability of having ears
     * @param t_shellProb the probability of having a shell
     * @param t_camoProb the probability of having a camo
     * @param t_finProb the probability of having a fin
     * @param t_behaviourDistrib [probGregarious, probFearful, probKamikaze, probMultiple]
     */
    RandomBuilder(CreatureBuilder &t_director, double t_eyeProb, double t_earProb, double t_shellProb,
                  double t_camoProb,
                  double t_finProb, std::array<double, 4> t_behaviourDistrib);

    explicit RandomBuilder(CreatureBuilder &t_director);

    void initID(int t_id) override;

    void initAccessories() override;

    void initSensors() override;

    void initBehaviour() override;

    void initPosition() override;

    void initVitesse() override;

    void initLifetimeDuration() override;

    void initCreatureSize() override;

    std::unique_ptr<Creature> getResult() override;

    void reset() override;

private :
    CreatureBuilder &director;
    Creature m_creature;

    // random parameters
    double m_eyeProb = eyeProb;
    double m_earProb = earProb;
    double m_shellProb = shellProb;
    double m_camoProb = camoProb;
    double m_finProb = finProb;
    std::array<double, 4> m_behaviourDistrib = behaviourDistrib;

    array<double, 4> getCumDistrib();

    void normalizeDistrib();
};

class CloneBuilder : public BuilderInterface {
public:
    /**
     * Creates a creature from another creature
     * @param t_director director the builder refers to
     */

    explicit CloneBuilder(CreatureBuilder &t_director);

    void initID(int t_id) override;

    void initAccessories() override { };

    void initSensors() override { };

    void initBehaviour() override { };

    void initPosition() override ;

    void initVitesse() override;

    void initLifetimeDuration() override;

    void initCreatureSize() override { };

    std::unique_ptr<Creature> getResult() override;

    void reset() override ;

    void setCopy(Creature& creature);

private :
    CreatureBuilder &director;
    Creature m_creature;
    Creature creatureToCopy;
};

class CreatureBuilder {
public:
    explicit CreatureBuilder(Milieu &t_milieu) : milieu(t_milieu) {};

    CreatureBuilder(Milieu &t_milieu, BuilderInterface &t_builder) : milieu(
            t_milieu) { builder = std::shared_ptr<BuilderInterface>(&t_builder); };

    std::unique_ptr<Creature> make();
    std::unique_ptr<Creature> makeRandom();
    std::unique_ptr<Creature> makeClone();
    void setBuilder(std::shared_ptr<BuilderInterface> &t_builder) { builder = t_builder; };
    Milieu &milieu;
private:
    std::shared_ptr<BuilderInterface> builder;
    int next_ = 0;
};


#endif //AQUARIUM_CREATUREBUILDER_H
