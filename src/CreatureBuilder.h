//
// Created by minhtri on 21/03/2022.
//

#ifndef AQUARIUM_CREATUREBUILDER_H
#define AQUARIUM_CREATUREBUILDER_H
#include <memory>
#include "Creature.h"

class CreatureBuilder;

class BuilderInterface {
public :
    virtual void initID(int id) = 0;
    virtual void initAccessories() = 0;
    virtual void initSensors()= 0;
    virtual void initBehaviour() = 0;
    virtual void initPosition() = 0;
    virtual void initVitesse() = 0;
    virtual std::unique_ptr<Creature> getResult() = 0;
    virtual void reset() = 0;
};

class RandomBuilder : public BuilderInterface {
public:
    RandomBuilder(CreatureBuilder &t_director,double t_eyeProb, double t_earProb, double t_shellProb, double t_camoProb, double t_finProb, std::array<double, 4> t_behaviourDistrib);
    RandomBuilder(CreatureBuilder& t_director);
    void initID(int t_id) override;
    void initAccessories() override;
    void initSensors() override;
    void initBehaviour() override;
    void initPosition() override;
    void initVitesse() override;
    std::unique_ptr<Creature> getResult() override;
    void reset() override;
private :
    CreatureBuilder& director;
    Creature m_creature;

    // random parameters
    double m_eyeProb = 0.5;
    double m_earProb = 0.5;
    double m_shellProb = 0.5;
    double m_camoProb = 0.5;
    double m_finProb = 0.5;
    std::array<double, 4> m_behaviourDistrib {{0.25, 0.25, 0.25 ,0.25}};

    array<double, 4> getCumDistrib();
    void normalizeDistrib();
};


class CreatureBuilder {
public:
    CreatureBuilder(Milieu& t_milieu, BuilderInterface& t_builder ): milieu(t_milieu), builder(t_builder) {};
    std::unique_ptr<Creature> make(int creatureID);
    void setBuilder(BuilderInterface& t_builder) {builder = t_builder;};
    Milieu& milieu;
private:
    BuilderInterface& builder;
    int next_ = 0;
};


#endif //AQUARIUM_CREATUREBUILDER_H
