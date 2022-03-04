#ifndef _SENSORS_H_
#define _SENSORS_H_

class InterfaceSensors {
public:
    virtual std::tuple<float,float,float> detectionZone() =0 const;
    virtual float detectionCoef() const;
};

class Eyes:public InterfaceSensor {
public: 
    virtual std::tuple<float,float,float> detectionZone() const override;

private:
    float detectionCoef_;
    float detectionRadius_;
    float detectionAngle_;
}
class Ears:public InterfaceSensor {
public: 
    virtual std::tuple<float,float,float> detectionZone() const override;

private:
    float detectionCoef_;
}

#endif