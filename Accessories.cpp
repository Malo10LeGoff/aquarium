#include "Accessories.h"


Accessories::Accessories() 
{
    std::list<InterfaceAccessory> accessories_;
};


float Accessories::speedCoef() const
{
    float coef(1.0);
    std::list<InterfaceAccessory>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef = (it)->speedCoef();
    }
    return coef;
};

float Accessories::camoCoef() const
{
    float coef = 1;
    std::list<InterfaceAccessory>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef = (it)->camoCoef();
    }
    return coef;
};

float Accessories::deathCoef() const
{
    float coef = 1;
    std::list<InterfaceAccessory>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef = (it)->deathCoef();
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
    camoCoef_ = camoCoef;
};


float Camo::camoCoef() const
{
    return camoCoef_;
};

Fins::Fins(float speedCoef) 
{
    speedCoef_ = speedCoef;
};


float Fins::speedCoef() const
{
    return speedCoef_;
};