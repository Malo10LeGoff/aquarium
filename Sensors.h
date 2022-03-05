#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <iostream>
#include <vector>
#include <list>

class InterfaceSensors {
public:
    virtual bool detect(int x_a,int y_a,int x_b,int y_b,double orientation) const {return 0;};
};

class Sensors: public InterfaceSensors {
public:
    Sensors();
    bool detect(int x_a,int y_a,int x_b,int y_b,double orientation)  const;
    std::list<InterfaceSensors *> sensors_;
};

class Eyes:public InterfaceSensors {
public:
    Eyes(float detectionCoef,float detectionRadius,float detectionAngle);
    bool detect(int x_a,int y_a,int x_b,int y_b, double orientation) const;
private:
    float detectionCoef_;
    float detectionRadius_;
    float detectionAngle_;
};

class Ears:public InterfaceSensors {
public:
    Ears(float detectionCoef,float detectionRadius);
    bool detect(int x_a,int y_a,int x_b,int y_b,double orientation) const;
private:
    float detectionCoef_;
    float detectionRadius_;
};

#endif