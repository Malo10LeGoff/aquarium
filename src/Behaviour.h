

#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_
#include <array>
#include <vector>
#include <memory>
class InterfaceBehaviour {
public:
    /**
     *
     * @param visibleCreatures
     *          vector of [array<float,2> moveDirection, array<float,2> coordinates]
     * @return moveDirection
     *          std::array<float,2> The direction the creature wants to move.
     */
    virtual std::array<float,2> moveDirection(const std::array<float,2> creatureCoordinates, const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const = 0;
    virtual float moveSpeedMultiplier(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const {
        return 1;
    };

    virtual std::unique_ptr<InterfaceBehaviour> clone() const = 0 ;
};

class GregariousBehaviour: public InterfaceBehaviour {
public:
    GregariousBehaviour();
    std::array<float,2> moveDirection(const std::array<float,2> creatureCoordinates, const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
};

class FearfulBehaviour: public InterfaceBehaviour {
public:
    FearfulBehaviour();
    FearfulBehaviour(int maxNeighbours, float moveSpeedMultiplier): moveSpeedMultiplier_(moveSpeedMultiplier), maxNeighbours_(maxNeighbours) { };
    std::array<float,2> moveDirection(const std::array<float,2> creatureCoordinates,const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    float moveSpeedMultiplier(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    int maxNeighbours() const;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
private:
    float moveSpeedMultiplier_;
    int maxNeighbours_;
};

class KamikazeBehaviour: public InterfaceBehaviour {
public:
    KamikazeBehaviour();
    explicit KamikazeBehaviour(float t_moveSpeedMultiplier) : m_moveSpeedMultiplier(t_moveSpeedMultiplier) {};
    std::array<float,2> moveDirection(const std::array<float,2> creatureCoordinates, const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
private:
    float m_moveSpeedMultiplier = 1;
};

class PlanningBehaviour:public InterfaceBehaviour {
public:
    std::array<float,2> moveDirection(const std::array<float,2> creatureCoordinates ,const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
};

class MultipleBehaviours: public InterfaceBehaviour {
public:
    MultipleBehaviours();
    std::array<float, 2> moveDirection(const std::array<float, 2> creatureCoordinates, const std::vector<std::array<std::array<float, 2>, 2>> visibleCreatures) const override;
    void add(std::unique_ptr<InterfaceBehaviour>& behaviour);
    void remove(int index);
    std::unique_ptr<InterfaceBehaviour> clone() const override;
private:
    std::vector<std::unique_ptr<InterfaceBehaviour>> behaviours_;
};
#endif //_BEHAVIOUR_H_
