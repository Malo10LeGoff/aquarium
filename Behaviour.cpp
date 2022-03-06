#include <Behaviour.h>

std::array<float,2> GregariousBehaviour::moveDirection(const std::vector<std::array<std::array<float,2>,2>> visibleCreatures) const {
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