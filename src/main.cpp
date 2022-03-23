#include "Aquarium.h"
#include "Milieu.h"
#include "Creature.h"
#include "Sensors.h"
#include "Accessories.h"
#include <iostream>
#include "constants.h"

using namespace std;


int main() {


    Aquarium ecosysteme(screenWidthPX, screenHeightPX, 30);
    for (int i = 1; i <= 200; ++i)
        ecosysteme.getMilieu().addRandomMember();
    ecosysteme.run();

    return 0;

}
