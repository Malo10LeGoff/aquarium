//
// Created by minhtri on 18/03/2022.
//

#ifndef AQUARIUM_HITBOX_H
#define AQUARIUM_HITBOX_H
#include "Vector.h"
/*
struct HitboxInterface {
    virtual bool isColliding(const HitboxInterface hitbox);
};
*/

struct CircleHitbox {
    CircleHitbox() = default;
    CircleHitbox(Vector& t_center, float t_radius): center(t_center), radius(t_radius) {};

    Vector center {0,0};
    float radius = 0;

    bool isColliding(const CircleHitbox hitbox) const ;
};


#endif //AQUARIUM_HITBOX_H
