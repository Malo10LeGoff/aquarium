#include "Accessories.h"


Accessories::Accessories() 
{
    //add Shell
    if (rand()%2==1){
      float speedRed = -static_cast<float>(rand()) / RAND_MAX * 3;
      float deathCo = static_cast<float>(rand()) / (3*RAND_MAX);
      Shell *ptr_s = new Shell(speedRed,deathCo);
      accessories_.push_back(ptr_s); // accessories à passer private
    }
   //add Fins
    if (rand()%2 ==1){
      float speedBoost = static_cast<float>(rand()) / RAND_MAX * 3;
      Fins *ptr_f = new Fins(speedBoost);
      accessories_.push_back(ptr_f);
    }

   //add Camo
    if (rand()%2==1){
      float camoBoost = static_cast<float>(rand()) / RAND_MAX * 3;
      Camo *ptr_c = new Camo(camoBoost);
      accessories_.push_back(ptr_c);
   }
    
}


float Accessories::speedCoef() const
{
    float coef(0);
    std::list<InterfaceAccessory *>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef += (*it)->speedCoef();
    }
    return coef;
}

float Accessories::camoCoef() const
{
    float coef = 0;
    std::list<InterfaceAccessory *>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef += (*it)->camoCoef();
    }
    return coef;
}

float Accessories::deathCoef() const
{
    float coef = 0;
    std::list<InterfaceAccessory *>::const_iterator it;
    for (it=accessories_.begin();it!= accessories_.end();it++) {
        coef += (*it)->deathCoef();
    }
    return coef;
}


Shell::Shell(float speedReductionCoef, float deathCoef) 
{
    speedReductionCoef_ = speedReductionCoef;
    deathCoef_ = deathCoef;
}

int Shell::AccessoryType() const
{
    return 1;
}

float Shell::speedCoef() const
{
    return speedReductionCoef_;
}

float Shell::deathCoef() const
{
    return deathCoef_;
}

Camo::Camo(float camoCoef) 
{
    camoCoef_ = camoCoef;
}

int Camo::AccessoryType() const
{
    return 2;
}


float Camo::camoCoef() const
{
    return camoCoef_;
}

Fins::Fins(float speedCoef) 
{
    speedCoef_ = speedCoef;
}


float Fins::speedCoef() const
{
    return speedCoef_;
}

int Fins::AccessoryType() const
{
    return 3;
}
