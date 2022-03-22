

#ifndef _BEHAVIOUR_H_
#define _BEHAVIOUR_H_
#include <array>
#include <vector>
#include <memory>
#include "../lib/Vector.h"
#include "../lib/UImg.h"

class InterfaceBehaviour {
public:
    /**
     *
     * @param visibleCreatures
     *          vector of [array<float,2> moveDirection, array<float,2> coordinates]
     * @return moveDirection
     *          std::array<float,2> The direction the creature wants to move.
     */
    virtual Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const = 0;
    virtual float moveSpeedMultiplier(const std::vector<std::array<Vector,2>> visibleCreatures) const {
        return 1;
    };

    virtual unsigned char * getColor() = 0 ;
    virtual std::unique_ptr<InterfaceBehaviour> clone() const = 0 ;
};

class GregariousBehaviour: public InterfaceBehaviour {
public:
    GregariousBehaviour() = default; // default cosntructor
    GregariousBehaviour(const GregariousBehaviour & g) = default; // copy constructor
    GregariousBehaviour& operator=(const GregariousBehaviour& g) = default; // assign copy
    ~GregariousBehaviour()=default; // Destructor
    Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
    static unsigned char couleur[];
    unsigned char * getColor();
};

class FearfulBehaviour: public InterfaceBehaviour {
public:
    FearfulBehaviour();
    FearfulBehaviour(int maxNeighbours, float moveSpeedMultiplier): moveSpeedMultiplier_(moveSpeedMultiplier), maxNeighbours_(maxNeighbours) { };
    FearfulBehaviour(const FearfulBehaviour & f); // copy constructor
    ~FearfulBehaviour()= default ; // destructor
    FearfulBehaviour& operator=(const FearfulBehaviour& f); // copy assign
    Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    float moveSpeedMultiplier(const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    int maxNeighbours() const;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
    static unsigned char couleur[];
    unsigned char * getColor();
private:
    float moveSpeedMultiplier_ =1;
    int maxNeighbours_ = 10;
};

class KamikazeBehaviour: public InterfaceBehaviour {
public:
    KamikazeBehaviour() = default ;
    explicit KamikazeBehaviour(float t_moveSpeedMultiplier) : m_moveSpeedMultiplier(t_moveSpeedMultiplier) {};
    KamikazeBehaviour(const KamikazeBehaviour & k); // copy constructor
    KamikazeBehaviour& operator= (const KamikazeBehaviour& k );
    ~KamikazeBehaviour() = default;
    Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
    static unsigned char couleur[];
    unsigned char * getColor();
private:
    float m_moveSpeedMultiplier = 1;
};

class PlanningBehaviour:public InterfaceBehaviour {
public:
    PlanningBehaviour()=default;
    PlanningBehaviour(const PlanningBehaviour& p);
    ~PlanningBehaviour() = default;
    PlanningBehaviour& operator=(const PlanningBehaviour& p);
    Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    std::unique_ptr<InterfaceBehaviour> clone() const override;
    static unsigned char couleur[];
    unsigned char * getColor();
private:
    float m_moveSpeedMultiplier = 1;
};

class MultipleBehaviours: public InterfaceBehaviour {
public:
    MultipleBehaviours();
    MultipleBehaviours(const MultipleBehaviours& m); // copy constructor
    MultipleBehaviours& operator=(const MultipleBehaviours& m); // copy assign constructor
    ~MultipleBehaviours()=default; // destructor

    Vector moveDirection(const Vector creatureCoordinates, const std::vector<std::array<Vector,2>> visibleCreatures) const override;
    void add(std::unique_ptr<InterfaceBehaviour>& behaviour);
    void remove(int index);
    std::unique_ptr<InterfaceBehaviour> clone() const override;
    int size() const ;
    static unsigned char couleur[];
    unsigned char * getColor();
private:
    std::vector<std::unique_ptr<InterfaceBehaviour>> behaviours_;
};
#endif //_BEHAVIOUR_H_
