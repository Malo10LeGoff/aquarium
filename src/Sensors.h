#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <string>
// detection caract = [ detectionCoef, detectionRadius, detectionAngle ]
typedef std::array<float,3> detection_caract;


class InterfaceSensors {
public:
    virtual std::string getType() const {return "sensors";};
    virtual std::vector<detection_caract> getDetectionZone() = 0;
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
    std::vector<detection_caract> getDetectionZone() override;
};

class Eyes:public InterfaceSensors {
public:

    Eyes(float detectionCoef,float detectionRadius,float detectionAngle);
    std::string getType() const override;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    float getDetectionAngle() const override;
    std::vector<detection_caract> getDetectionZone() override;

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
    std::vector<detection_caract> getDetectionZone() override;

private:
    std::string type;
    float detectionCoef_;
    float detectionRadius_;
};

#endif