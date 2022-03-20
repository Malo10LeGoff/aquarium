#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <iostream>
#include <vector>
#include <list>
#include <string>

class InterfaceSensors {
public:
    virtual std::string getType() const {return "sensors";};
    virtual float getDetectionRadius() const {return 0;};
    virtual float getDetectionCoef() const {return 0;};
    virtual float getDetectionAngle() const {return 0;};
};

class Sensors: public InterfaceSensors {
public:
    Sensors();
    std::list<InterfaceSensors *> sensors_;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    float getDetectionAngle() const override;
};

class Eyes:public InterfaceSensors {
public:

    Eyes(float detectionCoef,float detectionRadius,float detectionAngle);
    std::string getType() const override;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    float getDetectionAngle() const override;

private:
    std::string type;
    float detectionCoef_;
    float detectionRadius_;
    float detectionAngle_;
};

class Ears:public InterfaceSensors {
public:
    Ears(float detectionCoef,float detectionRadius);
    std::string getType() const override;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;

private:
    std::string type;
    float detectionCoef_;
    float detectionRadius_;
};

#endif