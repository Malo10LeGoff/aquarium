#include "Behaviour.h"
#include <cmath>
#include <algorithm>
#include "../lib/random_selection.cpp"
// GregariousBehaviour

GregariousBehaviour::GregariousBehaviour() {

}
std::array<float,2> GregariousBehaviour::moveDirection(const std::array<float,2> creatureCoordinates,
                                                       const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const {
    float cumX = 0;
    float cumY = 0;
    for (auto it = std::begin(visibleCreatures); it != std::end(visibleCreatures); ++it){
        // *it is [moveDirection , coordinates]
        cumX += (*it)[0][0];
        cumY += (*it)[0][1];

    }
    cumX /= visibleCreatures.size();
    cumY /= visibleCreatures.size();
    // Normalize the vector
    float d = sqrt(std::pow(cumX,2) + pow(cumY , 2));
    cumX /= d;
    cumY /= d;
    // scale by the speed
    cumX *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
    cumY *= InterfaceBehaviour::moveSpeedMultiplier(visibleCreatures);
    return std::array<float,2>{cumX, cumY};
}


// FearfulBehaviour
FearfulBehaviour::FearfulBehaviour() {
    moveSpeedMultiplier_ = 1.1;
    maxNeighbours_ = 10;
}

int FearfulBehaviour::maxNeighbours() const {
    return maxNeighbours_;
}

float FearfulBehaviour::moveSpeedMultiplier(const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) const {
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
std::array<float, 2> FearfulBehaviour::moveDirection(const std::array<float,2> creatureCoordinates,
                                                     const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) const {
    float x = 0;
    float y = 0;
    if (visibleCreatures.size() > (unsigned)this->maxNeighbours_) {
        // Calculate the running direction
        for (auto it= std::begin(visibleCreatures); it != std::end(visibleCreatures); ++it) {
            // *it is [moveDirection , coordinates]
            x+= (*it)[1][0] - creatureCoordinates[0];
            y+= (*it)[1][1] - creatureCoordinates[1];
        };
        x /= visibleCreatures.size();
        y /= visibleCreatures.size();
        // Normalize the direction
        float d = sqrt(std::pow(x,2) + pow(y , 2));
        x /= d;
        y /= d;
        // scale by the speed
        x *= this->moveSpeedMultiplier(visibleCreatures);
        y *= this->moveSpeedMultiplier(visibleCreatures);
    }
    return std::array<float,2>{x, y};
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


// MultipleBehaviours
MultipleBehaviours::MultipleBehaviours() {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>>{};
}

void MultipleBehaviours::add(std::unique_ptr<InterfaceBehaviour>& behaviour) {
    this->behaviours_.push_back(std::move(behaviour));
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


