

#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_
#include <array>
#include <vector>

class InterfaceBehaviour {
public:
    /**
     *
     * @param visibleCreatures
     *          vector of [array<float,2> moveDirection, array<float,2> coordinates]
     * @return moveDirection
     *          std::array<float,2> The direction the creature wants to move.
     */
    virtual std::array<float,2> moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const = 0;
    virtual float moveSpeedMultiplier(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const {
        return 1;
    };

};

class GregariousBehaviour: public InterfaceBehaviour {
public:
    std::array<float,2> moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
};

class FearfulBehaviour: public InterfaceBehaviour {
public:
    std::array<float,2> moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    float moveSpeedMultiplier();
private:
    float moveSpeedMultiplier_;
};

class KamikazeBehaviour: public InterfaceBehaviour {
public:
    std::array<float,2> moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
};

class PlanningBehaviour:public InterfaceBehaviour {
public:
    std::array<float,2> moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
};
#endif //_BEHAVIOUR_H_
