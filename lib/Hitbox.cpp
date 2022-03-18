//
// Created by minhtri on 18/03/2022.
//

#include "Hitbox.h"

bool CircleHitbox::isColliding(const CircleHitbox hitbox) {
    return radius + hitbox.radius <= distance(center, hitbox.center);
}
