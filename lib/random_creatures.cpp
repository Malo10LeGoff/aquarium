
#include <random>
#include "../src/constants.h"
#include "Vector.h"

// Parameter sampling functions
double clip(double value, double lower, double higher) {
    return std::max(lower, std::min(higher, value));
}

double randomShellSpeedCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxSpeedShell + minSpeedShell) / 2;
    // std so that 95% are between min and max
    double const stddev = (maxSpeedShell - mean) / 2;
    std::normal_distribution<double> shellSpeed (mean, stddev);

    return clip(shellSpeed(mt), 0 , 1);
}

double randomShellDeathCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxDeathCoefShell + minDeathCoefShell) / 2;
    // std so that 95% are between min and max
    double const stddev = (maxDeathCoefShell - mean) / 2;
    std::normal_distribution<double> shellDeath (mean, stddev);

    return clip(shellDeath(mt), 0, 1);
}

double randomCamoCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxCamoCoefCamo + minCamoCoefCamo) / 2;
    // std so that 95% are between min and max
    double const stddev = (maxCamoCoefCamo - mean) / 2;
    std::normal_distribution<double> camoCoef (mean, stddev);

    return clip(camoCoef(mt), minCamoCoefCamo, maxCamoCoefCamo);
}

double randomSpeedCoefFins() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxSpeedFins + minSpeedFins) / 2;
    // std so that 95% are between min and max
    double const stddev = (maxSpeedFins - mean) / 2;
    std::normal_distribution<double> finSpeed (mean, stddev);

    return finSpeed(mt);
}

Vector randomPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> y (0 , screenHeightPX);
    std::uniform_int_distribution<> x (0, screenWidthPX);

    return Vector (x(mt), y(mt));
}

Vector randomSpeed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const stddev = 0.25 * baseSpeed;
    std::normal_distribution<> speed (baseSpeed, stddev);
    std::uniform_real_distribution<> radian (0, 2 * M_PI);
    return speed(mt) * Vector(1,0).rotate(radian(mt));
}

double randomBaseSpeed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    const double mean = baseSpeed;
    const double stddev = (1.3*baseSpeed - baseSpeed) / 2;
    std::normal_distribution<> randomBaseSpeed (mean, stddev);
    return randomBaseSpeed(mt);
}

double randomDetectionAngleEyes() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxDetectionAngleEyes +  minDetectionAngleEyes ) / 2;
    double const stddev = (maxDetectionAngleEyes -  mean) / 2;
    std::normal_distribution<> eyesDetectionAngle (mean, stddev );
    return clip(eyesDetectionAngle(mt), 0 , 2* M_PI);
}

double randomRadiusEyes() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxRadiusEyes + minRadiusEyes) /2;
    double const stddev = (maxRadiusEyes - mean) / 2;
    std::normal_distribution<> eyesRadius (mean, stddev);
    return clip(eyesRadius(mt), 0, 100000000);
}

double randomDetectionCoefEyes() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxDetectionCoefEyes + minDetectionCoefEyes) /2;
    double const stddev = (maxDetectionCoefEyes - mean ) /3;
    std::normal_distribution<> eyesDetectionCoef (mean, stddev);
    return clip(eyesDetectionCoef(mt) , minDetectionCoef, maxDetectionCoef);
}

double randomRadiusEars() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxRadiusEars + minRadiusEars) /2;
    double const stddev = (maxRadiusEars - mean ) /2;
    std::normal_distribution<> earsRadius (mean, stddev);
    return clip(earsRadius(mt) , 0, 100000000);
}

double randomDetectionCoefEars() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxDetectionCoefEars + minDetectionCoefEars) /2;
    double const stddev = (maxDetectionCoefEars - mean ) /3;
    std::normal_distribution<> earsDetectionCoef (mean, stddev);
    return clip(earsDetectionCoef(mt) , minDetectionCoef, maxDetectionCoef);
}

int randomMaxNeighboursFearful() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = ( maxMaxNeighbours + minMaxNeighbours) / 2.0 ;
    double const stddev = (maxMaxNeighbours - mean) / 2.0;
    std::normal_distribution< > maxNeighbours (mean, stddev);
    return static_cast<int>(clip(round(maxNeighbours(mt)), 0, 100));
}

double randomFleeingSpeed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxFleeingSpeed + minFleeingSpeed) /2.0;
    double const stddev = (maxFleeingSpeed -mean) / 2.0;
    std::normal_distribution<> fleeingSpeed (mean, stddev);
    return clip(fleeingSpeed(mt), 0, 10);
}

double randomSpeedKamikaze( ) {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxSpeedKamikaze + minSpeedKamikaze) / 2.0;
    double const stddev = (maxSpeedKamikaze - mean ) / 2;
    std::normal_distribution<> speedKamikaze (mean, stddev);
    return clip(speedKamikaze(mt), 0, 10);
}

int randomDyingAge() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxDyingAge + minDyingAge) /2.0 ;
    double const stddev = (maxDyingAge - mean )  ;
    std::normal_distribution<> lifetimeDuration (mean, stddev);
    return static_cast<int>(lifetimeDuration(mt));
}

double randomCreatureSize() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double const mean = (maxSize + minSize) / 2.0;
    double const stddev = (maxSize - mean) /2.0;
    std::normal_distribution<> creatureSize (mean, stddev);
    return clip(creatureSize(mt),1, 100);
}

std::uniform_int_distribution<> getRandomIntDistrib(int a, int b) {
    std::random_device rd;
    std::mt19937 mt(rd());
    return std::uniform_int_distribution<> (a,b);
}

