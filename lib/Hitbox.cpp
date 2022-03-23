//
// Created by minhtri on 18/03/2022.
//

#include "Hitbox.h"
#include <iostream>


bool CircleHitbox::isColliding(const CircleHitbox hitbox) const {
    //std::cout << "radius " << radius << " hitbox radius " << hitbox.radius << " distance " << int(distanceVectors(center,hitbox.center)) << std::endl;
    return radius + hitbox.radius >= distanceVectors(center, hitbox.center);
}
