#include <Behaviour.h>

std::tuple<float,float> GregariousBehaviour::moveDirection(const std::list<Creature&> visibleCreatures) {
    int counter = 0;
    float cumX = 0;
    float cumY = 0;
    for (auto it = visibleCreatures.begin(); it != visibleCreatures.end(); it++){
        tuple<float,float>& coordinate = *it.coordinates();

    }
};