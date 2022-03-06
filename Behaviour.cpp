#include <Behaviour.h>
#include <cmath>
// GregariousBehaviour

GregariousBehaviour::GregariousBehaviour() {

};
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
    return std::array<float,2>{cumX, cumY};
};


// FearfulBehaviour
FearfulBehaviour::FearfulBehaviour() {
    moveSpeedMultiplier_ = 1.1;
    maxNeighbours_ = 10;
};

FearfulBehaviour::FearfulBehaviour(int maxNeighbours, float moveSpeedMultiplier) {
    moveSpeedMultiplier_ = moveSpeedMultiplier;
    maxNeighbours_ = maxNeighbours;
};

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
    }
    return std::array<float,2>{x, y};
};

float FearfulBehaviour::moveSpeedMultiplier(const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) {
    if (visibleCreatures.size() > (unsigned)this->maxNeighbours_) {
        return this->moveSpeedMultiplier_;
    }
    else {
        return 1;
    }
}

// KamikazeBehaviour
KamikazeBehaviour::KamikazeBehaviour(){

};

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
    // calculate the neighbours' distances
    // we calculate the squared dxistnace for performance reasons
    std::vector<float> neighbourDistances;
    for (auto it= std::begin(visibleCreatures); it != std::end(visibleCreatures); ++it) {
        // *it is [moveDirection , coordinates]
        float d = std::pow((*it)[1][0] - creatureCoordinates[0], 2) + std::pow((*it)[1][1] - creatureCoordinates[1], 2);
        neighbourDistances.push_back(d);
    };
    int closest_neighbour_idx = min_element(neighbourDistances);
    return std::array<float,2> { visibleCreatures[closest_neighbour_idx][1][0] - creatureCoordinates[0],
                                 visibleCreatures[closest_neighbour_idx][1][1] - creatureCoordinates[1]};

};


// MultipleBehaviours
MultipleBehaviours::MultipleBehaviours() {
    behaviours_ = std::vector<std::unique_ptr<InterfaceBehaviour>>{};
}

void MultipleBehaviours::add(std::unique_ptr<InterfaceBehaviour>& behaviour) {
    this->behaviours_.push_back(std::move(behaviour));
}

float MultipleBehaviours::moveSpeedMultiplier(const std::vector<std::array<std::array < float, 2>, 2>> visibleCreatures) const {
    return 1;
}
