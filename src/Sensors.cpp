#include "Sensors.h"
#include <math.h>


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

float Sensors::getDetectionRadius() const
{
    return 0;
};

float Sensors::getDetectionAngle() const
{
    return 0;
};

float Sensors::getDetectionCoef() const
{
    return 0;
};

Eyes::Eyes(float detectionCoef,float detectionRadius,float detectionAngle) 
{
    type = "Eyes";
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
    detectionAngle_= detectionAngle;
};

std::string Eyes::getType() const
{
    return type;
};

float Eyes::getDetectionRadius() const
{
    return detectionRadius_;
};

float Eyes::getDetectionAngle() const
{
    return detectionAngle_;
};

float Eyes::getDetectionCoef() const
{
    return detectionCoef_;
};


Ears::Ears(float detectionCoef,float detectionRadius) 
{
    type = "Ears";
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
};

std::string Ears::getType() const
{
    return type;
};

float Ears::getDetectionRadius() const
{
    return detectionRadius_;
};

float Ears::getDetectionCoef() const
{
    return detectionCoef_;
};
