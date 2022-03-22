#define _USE_MATH_DEFINES
#include "Sensors.h"
#include <cmath>



float Sensors::getDetectionRadius() const
{
    return 0;
}

float Sensors::getDetectionAngle() const
{
    return 0;
}

float Sensors::getDetectionCoef() const
{
    return 0;
}

std::vector<detection_caract> Sensors::getDetectionZone() {
    std::vector<detection_caract> ret {} ;
    for (auto const& sensor: sensors_) {
        ret.push_back(sensor->getDetectionZone()[0]);
    }
    return ret;
}

void Sensors::add(std::unique_ptr<InterfaceSensors>& sensor) {
    sensors_.push_back(std::move(sensor));
}

void Sensors::remove(int idx) {
    // TODO
}

Sensors::Sensors(const Sensors &s) {
    sensors_ = std::vector<std::unique_ptr<InterfaceSensors>> { };
    for (auto const& sensor : s.sensors_) {
        sensors_.push_back(sensor->clone());
    }
}

Sensors &Sensors::operator=(const Sensors &s) {
    sensors_ = std::vector<std::unique_ptr<InterfaceSensors>> {};
    for (auto const& sensor : s.sensors_) {
        sensors_.push_back(sensor->clone());
    }
    return *this;
}

std::unique_ptr<InterfaceSensors> Sensors::clone() {
    return std::unique_ptr<InterfaceSensors>(new Sensors(*this));
}

Eyes::Eyes(float detectionCoef,float detectionRadius,float detectionAngle) 
{
    type = "Eyes";
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
    detectionAngle_= detectionAngle;
}

std::string Eyes::getType() const
{
    return type;
}

float Eyes::getDetectionRadius() const
{
    return detectionRadius_;
}

float Eyes::getDetectionAngle() const
{
    return detectionAngle_;
}

float Eyes::getDetectionCoef() const
{
    return detectionCoef_;
}

std::vector<detection_caract> Eyes::getDetectionZone() {
    return std::vector<detection_caract> { {detectionCoef_, detectionRadius_, detectionAngle_} };
}

Eyes::Eyes(const Eyes &e) {
    type = e.type;
    detectionRadius_ = e.detectionRadius_;
    detectionCoef_ = e.detectionCoef_;
    detectionAngle_ = e.detectionAngle_;
}

Eyes &Eyes::operator=(const Eyes &eyes) {
    type = eyes.type;
    detectionRadius_ = eyes.detectionRadius_;
    detectionCoef_ = eyes.detectionCoef_;
    detectionAngle_ = eyes.detectionAngle_;
    return *this;
}

std::unique_ptr<InterfaceSensors> Eyes::clone() {
    return std::unique_ptr<InterfaceSensors>(new Eyes(*this));
}


Ears::Ears(float detectionCoef,float detectionRadius) 
{
    type = "Ears";
    detectionCoef_ = detectionCoef;
    detectionRadius_ = detectionRadius;
    detectionAngle_= 2*M_PI;
}

std::string Ears::getType() const
{
    return type;
}

float Ears::getDetectionRadius() const
{
    return detectionRadius_;
}

float Ears::getDetectionCoef() const
{
    return detectionCoef_;
}

float Ears::getDetectionAngle() const
{
    return detectionAngle_;
}

std::vector<detection_caract> Ears::getDetectionZone() {
    return std::vector<detection_caract> { {detectionCoef_, detectionRadius_ , 2 * M_PI }};
}

Ears::Ears(const Ears &e) {
    detectionCoef_ = e.detectionCoef_;
    detectionRadius_ = e.detectionRadius_;
    type = e.type;
}

Ears &Ears::operator=(const Ears &e) {
    detectionCoef_ = e.detectionCoef_;
    detectionRadius_ = e.detectionRadius_;
    type = e.type;
    return *this;
}

std::unique_ptr<InterfaceSensors> Ears::clone() {
    return std::unique_ptr<InterfaceSensors>(new Ears(*this));
}


