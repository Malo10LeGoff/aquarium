#include "Accessories.h"


Accessories::Accessories() 
{
    accessories_ = std::list<InterfaceAccessory&>
};


float Accessories::speedCoef() const
{
    float coef = 1;
    std::list<InterfaceAccessory&>::iterator a;
    for (a=accessories_.begin();a!= accessories_.end();a++) {
        coef *= a.speedCoef();
    }
    return coef;
};

float Accessories::camoCoef() const
{
    float coef = 1;
    std::list<InterfaceAccessory&>::iterator a;
    for (a=accessories_.begin();a!= accessories_.end();a++) {
        coef *= a.camoCoef();
    }
    return coef;
};

float Accessories::deathCoef() const
{
    float coef = 1;
    std::list<InterfaceAccessory&>::iterator a;
    for (a=accessories_.begin();a!= accessories_.end();a++) {
        coef *= a.deathCoef();
    }
    return coef;
};


Shell::Shell(float speedReductionCoef, float deathCoef) 
{
    speedReductionCoef_ = speedReductionCoef;
    deathCoef_ = deathCoef;
};


float Shell::speedCoef() const
{
    return speedReductionCoef_;
};

float Shell::deathCoef() const
{
    return deathCoef_;
};

Camo::Camo(float camoCoef) 
{
    camoCoef_ = camoCoef
};


float Camo::camoCoef() const
{
    return camoCoef_;
};

Fins::Fins(float speedCoef) 
{
    speedCoef_ = speedCoef
};


float Fins::speedCoef() const
{
    return speedCoef_;
};