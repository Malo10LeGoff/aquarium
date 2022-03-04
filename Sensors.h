#ifndef _SENSORS_H_
#define _SENSORS_H_

class InterfaceSensors {
public:
    virtual std::list<std::tuple<float,float>> detectionZone() const =0;
    virtual std::list<float> detectionCoef() const =0;
};

class Eyes:public InterfaceSensor {
public:
    std::list<std::tuple<float,float>> detectionZone() const override;

private:
    float detectionCoef_;
    float detectionRadius_;
    float detectionAngle_;
};

class Ears:public InterfaceSensor {
public:
    std::list<std::tuple<float,float>> detectionZone() const override;

private:
    float detectionCoef_;
};

#endif