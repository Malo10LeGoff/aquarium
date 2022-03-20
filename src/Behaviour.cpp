#include "Behaviour.h"
#include <cmath>
#include <algorithm>
#include "../lib/random_selection.cpp"
// GregariousBehaviour


Vector GregariousBehaviour::moveDirection(const Vector creatureCoordinates,
                                                       const std::vector<std::array<Vector,2>> visibleCreatures) const {
    Vector moveD {0, 0};
    for (auto const e: visibleCreatures){
        // e is [moveD , coordinates]
        moveD = moveD + e[0];
    }
    moveD.x /= visibleCreatures.size();
    moveD.y /= visibleCreatures.size();
    // Normalize the vector
    moveD = moveD.normalize();
    // scale by the speed
    moveD.x *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
    moveD.y *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
    return moveD;
}

std::unique_ptr<InterfaceBehaviour> GregariousBehaviour::clone() const {
    return std::unique_ptr<GregariousBehaviour>(new GregariousBehaviour(*this));
}



// FearfulBehaviour
FearfulBehaviour::FearfulBehaviour() {
    moveSpeedMultiplier_ = 1.1;
    maxNeighbours_ = 10;
}

int FearfulBehaviour::maxNeighbours() const {
    return maxNeighbours_;
}

float FearfulBehaviour::moveSpeedMultiplier(const std::vector<std::array<Vector, 2>> visibleCreatures) const {
if (visibleCreatures.size() > (unsigned)this->maxNeighbours_) {
    return this->moveSpeedMultiplier_;}
else {
return 1;
}
}

/**
 * If there's too many people detected, then run in opposite of the mean directions
 * the other creatures are in.
 * Will return [0,0] if there's no change of direction planned
 */
Vector FearfulBehaviour::moveDirection(const Vector creatureCoordinates,
                                                     const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    Vector moveD {0,0};
    if (visibleCreatures.size() > (unsigned)this->maxNeighbours_) {
        // Calculate the running direction
        for (auto const neighbour : visibleCreatures ){
            // *it is [moveDirection , coordinates]
            moveD = moveD + neighbour[1] - creatureCoordinates;
        };
        moveD = moveD.normalize();
        // scale by the speed
        moveD.x *= this->moveSpeedMultiplier(visibleCreatures);
        moveD.y *= this->moveSpeedMultiplier(visibleCreatures);
    }
    return moveD;
}

std::unique_ptr<InterfaceBehaviour> FearfulBehaviour::clone() const {
    return std::unique_ptr<FearfulBehaviour>(new FearfulBehaviour(*this));
}

FearfulBehaviour::FearfulBehaviour(const FearfulBehaviour &f): moveSpeedMultiplier_(f.moveSpeedMultiplier_), maxNeighbours_(f.maxNeighbours_) {

}

FearfulBehaviour &FearfulBehaviour::operator=(const FearfulBehaviour &f) {
    moveSpeedMultiplier_ = f.moveSpeedMultiplier_;
    maxNeighbours_ = f.maxNeighbours_;
    return *this;
}


// KamikazeBehaviour
KamikazeBehaviour::KamikazeBehaviour(){

}

int min_element(const std::vector<float> arr) {
    int index =0;
    for (int i=0; (unsigned)i< arr.size(); ++i) {
        if (arr[i] < arr[index] ) {
            index = i;
        }
    }
    return index;
}

/**
 * Run into the closest creature to the current creature
 * @param creatureCoordinates
 * @return [x,y] representing the direction to move in
 */
std::array<float, 2> KamikazeBehaviour::moveDirection(const std::array<float, 2> creatureCoordinates,
                                                      const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) const {
    // calculate the neighbours' (squared) distances
    std::vector<float> neighbourDistances;
    for (auto it= std::begin(visibleCreatures); it != std::end(visibleCreatures); ++it) {
        // *it is [moveDirection , coordinates]
        float d = std::pow((*it)[1][0] - creatureCoordinates[0], 2) + std::pow((*it)[1][1] - creatureCoordinates[1], 2);
        neighbourDistances.push_back(d);
    };
    // Select the closest neighbour
    int closest_neighbour_idx = min_element(neighbourDistances);
    // Calculate the direction
    float x = visibleCreatures[closest_neighbour_idx][1][0] - creatureCoordinates[0];
    float y = visibleCreatures[closest_neighbour_idx][1][1] - creatureCoordinates[1];
    // Normalize the vector
    float d = sqrt(std::pow(x,2) + pow(y , 2));
    if (d!=0) {
        x /= d;
        y /= d;
    }
    // scale by the speed
    x *= m_moveSpeedMultiplier;
    y *= m_moveSpeedMultiplier;
    return std::array<float,2> { x, y};

}

std::unique_ptr<InterfaceBehaviour> KamikazeBehaviour::clone() const {
    return std::unique_ptr<KamikazeBehaviour> (new KamikazeBehaviour(*this));
}

KamikazeBehaviour::KamikazeBehaviour(const KamikazeBehaviour &k): m_moveSpeedMultiplier(k.m_moveSpeedMultiplier) {

}

KamikazeBehaviour &KamikazeBehaviour::operator=(const KamikazeBehaviour &k) {
    m_moveSpeedMultiplier = k.m_moveSpeedMultiplier;
    return *this;
}


// MultipleBehaviours
MultipleBehaviours::MultipleBehaviours() {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>>{};
}

MultipleBehaviours::MultipleBehaviours(const MultipleBehaviours &m) {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>> { };
    for (auto const& e: m.behaviours_) {
        behaviours_.push_back(e->clone());
    }
}

void MultipleBehaviours::add(std::unique_ptr<InterfaceBehaviour> & behaviour) {
    behaviours_.push_back(std::move(behaviour));
}

std::array<float, 2> MultipleBehaviours::moveDirection(const std::array<float, 2> creatureCoordinates,
                                                       const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) const {
    // Sample a behaviour in the list
    random_selector<> selector{};
    return selector(this->behaviours_)->moveDirection(creatureCoordinates, visibleCreatures);
}

void MultipleBehaviours::remove(int index) {
    behaviours_.erase(behaviours_.begin() + index);
}

std::unique_ptr<InterfaceBehaviour> MultipleBehaviours::clone() const {
    return std::unique_ptr<MultipleBehaviours>(new MultipleBehaviours(*this));
}

MultipleBehaviours &MultipleBehaviours::operator=(const MultipleBehaviours &m) {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>> { };
    for (auto const& behaviour : m.behaviours_) {
        behaviours_.push_back(behaviour->clone());
    }
    return *this;
}

int MultipleBehaviours::size() const {
    return static_cast<int>(behaviours_.size());
}


std::unique_ptr<InterfaceBehaviour> PlanningBehaviour::clone() const {
    return std::unique_ptr<PlanningBehaviour>(new PlanningBehaviour(*this));
}

PlanningBehaviour::PlanningBehaviour(const PlanningBehaviour &p): m_moveSpeedMultiplier(p.m_moveSpeedMultiplier) {

}

std::array<float, 2> PlanningBehaviour::moveDirection(const std::array<float, 2> creatureCoordinates,
                                                      const std::vector<std::array<std::array<float, 2>, 2>> visibleCreatures) const {
    // TODO :
    return std::array<float, 2>{0,0};
}

PlanningBehaviour &PlanningBehaviour::operator=(const PlanningBehaviour &p) {
    m_moveSpeedMultiplier = p.m_moveSpeedMultiplier;
    return *this;
}
