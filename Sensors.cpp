#include "Sensors.h"
#include "Creature.h"
#include <math.h> 
#include <list>


Sensors::Sensors() 
{
    //add Ears
    if (rand()%2==1){
      float detectionCoef = static_cast<float>(rand()) / RAND_MAX;
      float detectionRadius = static_cast<float>(rand()) / RAND_MAX * 30 + 30;
      Ears *ptr_ear = new Ears(detectionCoef,detectionRadius);
      sensors_.push_back(ptr_ear);

   } else {
       Ears *ptr_ear = new Ears(0.5,30);
       sensors_.push_back(ptr_ear);
   }

   //add Eyes
    if (rand()%2==1){
      float detectionCoef = static_cast<float>(rand()) / RAND_MAX;
      float detectionRadius = static_cast<float>(rand()) / RAND_MAX * 30 + 30;
      float detectionAngle = static_cast<float>(rand()) / RAND_MAX * 2 *M_PI;
      Eyes *ptr_eye = new Eyes(detectionCoef,detectionRadius,detectionAngle);
      sensors_.push_back(ptr_eye);
   }
};

bool Sensors::detect(int x_a,int y_a,int x_b,int y_b,double orientation)  const
{
    bool coef(0);
    std::list<InterfaceSensors *>::const_iterator it;
    for (it=sensors_.begin();it!= sensors_.end();it++) {
        if ((*it)->detect(x_a,y_a,x_b,y_b,orientation)==1) {
            coef = 1;
        };
    }
    return coef;
};


Eyes::Eyes(float detectionCoef,float detectionRadius,float detectionAngle) 
{
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
    detectionAngle_= detectionAngle;
};

bool Eyes::detect(int x_a,int y_a,int x_b,int y_b,double orientation) const
{
    //les produits scalaires sont surement une meilleure solution
    double dist;
    dist = std::sqrt((x_a - x_b) * (x_a - x_b) + (y_a - y_b) * (y_a - y_b));
    if (dist <= detectionRadius_) {
        int new_x_b = static_cast<int>(x_b*cos(orientation) + y_b*sin(orientation) - x_a);
        int new_y_b = static_cast<int>(-x_b*sin(orientation) + y_b*cos(orientation)- y_a);

        double alpha = atan (new_y_b/new_x_b);

        if (abs(alpha)<detectionAngle_) {
            return 1;
        }
    }
    return 0;
};


Ears::Ears(float detectionCoef,float detectionRadius) 
{
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
};

bool Ears::detect(int x_a,int y_a,int x_b,int y_b,double orientation) const
{
    double dist;
    dist = std::sqrt((x_a - x_b) * (x_a - x_b) + (y_a - y_b) * (y_a - y_b));
    return (dist <= detectionRadius_);
};
