#include "Behaviour.h"
#include <cmath>
#include <algorithm>
#include "../lib/random_selection.cpp"
// GregariousBehaviour

unsigned char GregariousBehaviour::couleur[] = {200, 200, 200};
unsigned char FearfulBehaviour::couleur[] = {10, 200, 100};
unsigned char KamikazeBehaviour::couleur[] = {0, 0, 200};
unsigned char PlanningBehaviour::couleur[] = {0, 200, 0};
unsigned char MultipleBehaviours::couleur[] = {100, 200, 0};

Vector GregariousBehaviour::moveDirection(const Vector creatureCoordinates,
                                          const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    Vector moveD{0, 0};
    for (auto const e: visibleCreatures) {
        // e is [moveD , coordinates]
        moveD = moveD + e[0];
    }
    if (visibleCreatures.size() != 0) {
        moveD.x /= visibleCreatures.size();
        moveD.y /= visibleCreatures.size();
        // Normalize the vector
        moveD = moveD.normalize();
        // scale by the speed
        moveD.x *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
        moveD.y *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
    }

    return moveD;
}

std::unique_ptr<InterfaceBehaviour> GregariousBehaviour::clone() const {
    return std::unique_ptr<GregariousBehaviour>(new GregariousBehaviour(*this));
}

unsigned char *GregariousBehaviour::getColor() {

    return GregariousBehaviour::couleur;
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
    if (visibleCreatures.size() > (unsigned) this->maxNeighbours_) {
        return this->moveSpeedMultiplier_;
    } else {
        return 1;
    }
}

unsigned char *FearfulBehaviour::getColor() {

    return FearfulBehaviour::couleur;
}

/**
 * If there's too many people detected, then run in opposite of the mean directions
 * the other creatures are in.
 * Will return [0,0] if there's no change of direction planned
 */
Vector FearfulBehaviour::moveDirection(const Vector creatureCoordinates,
                                       const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    Vector moveD{0, 0};
    if ((visibleCreatures.size() > (unsigned) this->maxNeighbours_) && (visibleCreatures.size() != 0)) {
        // Calculate the running direction
        for (auto const neighbour: visibleCreatures) {
            // *it is [moveDirection , coordinates]
            moveD = moveD + neighbour[1] - creatureCoordinates;
        };
        moveD = moveD.normalize();
        // scale by the speed
        moveD.x *= -this->moveSpeedMultiplier(visibleCreatures);
        moveD.y *= -this->moveSpeedMultiplier(visibleCreatures);
    }
    return moveD;
}

std::unique_ptr<InterfaceBehaviour> FearfulBehaviour::clone() const {
    return std::unique_ptr<FearfulBehaviour>(new FearfulBehaviour(*this));
}

FearfulBehaviour::FearfulBehaviour(const FearfulBehaviour &f) : moveSpeedMultiplier_(f.moveSpeedMultiplier_),
                                                                maxNeighbours_(f.maxNeighbours_) {

}

FearfulBehaviour &FearfulBehaviour::operator=(const FearfulBehaviour &f) {
    moveSpeedMultiplier_ = f.moveSpeedMultiplier_;
    maxNeighbours_ = f.maxNeighbours_;
    return *this;
}


// KamikazeBehaviour

int min_element(const std::vector<float> arr) {
    int index = 0;
    for (int i = 0; (unsigned) i < arr.size(); ++i) {
        if (arr[i] < arr[index]) {
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
Vector KamikazeBehaviour::moveDirection(const Vector creatureCoordinates,
                                        const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    if (visibleCreatures.size() != 0) {
        // calculate the neighbours' (squared) distances
        std::vector<float> neighbourDistances;
        for (auto const creature: visibleCreatures) {
            // *it is [moveDirection , coordinates]
            neighbourDistances.push_back(distanceVectors(creature[1], creatureCoordinates));
        };
        // Select the closest neighbour
        int closest_neighbour_idx = min_element(neighbourDistances);
        // Calculate the direction
        Vector moveDirection = (visibleCreatures[closest_neighbour_idx][1] - creatureCoordinates).normalize();
        // scale by the speed
        moveDirection.x *= m_moveSpeedMultiplier;
        moveDirection.y *= m_moveSpeedMultiplier;
        return moveDirection;
    }
    return Vector{0, 0};

}

unsigned char *KamikazeBehaviour::getColor() {

    return KamikazeBehaviour::couleur;
}


std::unique_ptr<InterfaceBehaviour> KamikazeBehaviour::clone() const {
    return std::unique_ptr<KamikazeBehaviour>(new KamikazeBehaviour(*this));
}

KamikazeBehaviour::KamikazeBehaviour(const KamikazeBehaviour &k) : m_moveSpeedMultiplier(k.m_moveSpeedMultiplier) {

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
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>>{};
    for (auto const &e: m.behaviours_) {
        behaviours_.push_back(e->clone());
    }
}

void MultipleBehaviours::add(std::unique_ptr<InterfaceBehaviour> &behaviour) {
    behaviours_.push_back(std::move(behaviour));
}

Vector MultipleBehaviours::moveDirection(const Vector creatureCoordinates,
                                         const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    // Sample a behaviour in the list
    if (behaviours_.size() !=0) {
        random_selector<> selector{};
        return selector(this->behaviours_)->moveDirection(creatureCoordinates, visibleCreatures);
    }
    return Vector(0,0);

}

void MultipleBehaviours::remove(int index) {
    behaviours_.erase(behaviours_.begin() + index);
}

unsigned char *MultipleBehaviours::getColor() {

    return MultipleBehaviours::couleur;
}


std::unique_ptr<InterfaceBehaviour> MultipleBehaviours::clone() const {
    return std::unique_ptr<MultipleBehaviours>(new MultipleBehaviours(*this));
}

MultipleBehaviours &MultipleBehaviours::operator=(const MultipleBehaviours &m) {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>>{};
    for (auto const &behaviour: m.behaviours_) {
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

PlanningBehaviour::PlanningBehaviour(const PlanningBehaviour &p) : m_moveSpeedMultiplier(p.m_moveSpeedMultiplier) {

}

Vector PlanningBehaviour::moveDirection(const Vector creatureCoordinates,
                                        const std::vector<std::array<Vector, 2>> visibleCreatures) const {
    // TODO :
    return {0, 0};
}

PlanningBehaviour &PlanningBehaviour::operator=(const PlanningBehaviour &p) {
    m_moveSpeedMultiplier = p.m_moveSpeedMultiplier;
    return *this;
}

unsigned char *PlanningBehaviour::getColor() {

    return PlanningBehaviour::couleur;
}