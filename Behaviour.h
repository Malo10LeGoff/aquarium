

#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_
#include <tuple>
#include <list>

class Creature; //forward declaration

class InterfaceBehaviour {
public:
    virtual std::tuple<float,float> moveDirection(const std::list<Creature&> visibleCreatures) const = 0;
    virtual float moveSpeedMultiplier(const std::list<Creature&> visibleCreatures) const {
        return 1;
    };

};

class GregariousBehaviour: public InterfaceBehaviour {
public:
    std::tuple<float,float> moveDirection(const std::list<Creature&> visibleCreatures) override;
};

class FearfulBehaviour: public InterfaceBehaviour {
public:
    std::tuple<float,float> moveDirection(const std::list<Creature&> visibleCreatures) override;
    float moveSpeedMultiplier();
private:
    float moveSpeedMultiplier_;
};

class KamikazeBehaviour: public InterfaceBehaviour {
public:
    std::tuple<float,float> moveDirection(const std::list<Creature&> visibleCreatures) override;
};

class PlanningBehaviour:public InterfaceBehaviour {
public:
    std::tuple<float,float> moveDirection(const std::list<Creature&> visibleCreatures) override;
};
#endif //_BEHAVIOUR_H_
