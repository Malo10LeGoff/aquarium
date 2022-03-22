#ifndef _SENSORS_H_
#define _SENSORS_H_

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <memory>
// detection caract = [ detectionCoef, detectionRadius, detectionAngle ]
typedef std::array<float,3> detection_caract;


class InterfaceSensors {
public:
    virtual std::string getType() const {return "sensors";};
    virtual std::vector<detection_caract> getDetectionZone() = 0;
    virtual float getDetectionRadius() const {return 0;};
    virtual float getDetectionCoef() const {return 0;};
    virtual float getDetectionAngle() const {return 0;};
    virtual std::unique_ptr<InterfaceSensors> clone()= 0;
};

class Sensors: public InterfaceSensors {
public:
    Sensors() = default;
    Sensors(const Sensors& s);
    ~Sensors() = default;
    Sensors& operator=(const Sensors& s);
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    float getDetectionAngle() const override;
    std::vector<detection_caract> getDetectionZone() override;
    void add(std::unique_ptr<InterfaceSensors> &sensor);
    void remove(int idx);
    std::unique_ptr<InterfaceSensors> clone() override;

    std::vector<std::unique_ptr<InterfaceSensors> > sensors_;
};

class Eyes:public InterfaceSensors {
public:
    Eyes(float detectionCoef,float detectionRadius,float detectionAngle);
    Eyes(const Eyes& e);
    ~Eyes() = default;
    Eyes& operator=(const Eyes& eyes);
    std::string getType() const override;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    float getDetectionAngle() const override;
    std::vector<detection_caract> getDetectionZone() override;
    std::unique_ptr<InterfaceSensors> clone() override;

private:
    std::string type;
    float detectionCoef_;
    float detectionRadius_;
    float detectionAngle_;
};

class Ears:public InterfaceSensors {
public:
    Ears(float detectionCoef,float detectionRadius);
    Ears(const Ears& e);
    ~Ears() = default;
    Ears& operator=(const Ears& e);
    std::string getType() const override;
    float getDetectionRadius() const override;
    float getDetectionCoef() const override;
    std::vector<detection_caract> getDetectionZone() override;
    std::unique_ptr<InterfaceSensors> clone() override;

private:
    std::string type;
    float detectionCoef_;
    float detectionRadius_;
};

#endif