//
// Created by minhtri on 21/03/2022.
//

#ifndef AQUARIUM_CONSTANTS_H
#define AQUARIUM_CONSTANTS_H
#define _USE_MATH_DEFINES

#include <cmath>
#include <array>

// Global
const int screenWidthPX = 640;
const int screenHeightPX = 480;
const double maxDetectionCoef = 0.95;
const double minDetectionCoef = 0;
const double creatureSpawnRate = 15; // average number of simulation steps needed to get 1 new creature spawned
const double creatureCloneRate = 200; // average number of simulation steps needed to get 1 new creature cloned
// Accessories
// All coeficients are multiplicative
//     Shell
const double minSpeedShell = 0.6;
const double maxSpeedShell = 1;
const double minDeathCoefShell = 0.5;
const double maxDeathCoefShell = 1;

//      Camo
const double minCamoCoefCamo = 0;
const double maxCamoCoefCamo = 0.99 * maxDetectionCoef;

//      Fins
const double minSpeedFins = 1;
const double maxSpeedFins = 2;

// Behaviour
//      Fearful
const int maxMaxNeighbours = 6;
const int minMaxNeighbours = 2;
const double minFleeingSpeed = 1;
const double maxFleeingSpeed = 1.5;

// Kamikaze
const double minSpeedKamikaze = 1;
const double maxSpeedKamikaze = 1.5;

// Sensors
//      Eyes
const double minDetectionAngleEyes = M_PI / 4;
const double maxDetectionAngleEyes = M_PI/2;
const double minRadiusEyes = 30;
const double maxRadiusEyes = 60;
const double maxDetectionCoefEyes = maxDetectionCoef;
const double minDetectionCoefEyes = 0.2 * maxDetectionCoef;
//       Ears
const double minRadiusEars = 10;
const double maxRadiusEars = 30;
const double maxDetectionCoefEars = maxDetectionCoef * 0.3;
const double minDetectionCoefEars = maxDetectionCoefEyes * 0.0001;

// Creature
const double minSize = 5;
const double maxSize = 20;
const double baseSpeed = 5;
const double time_delta = 1;
const int minDyingAge = 500;
const int maxDyingAge = 1000;
const float baseCreatureCamoCoef = 0.05;

// Random init parameters
double const eyeProb = 0.5;
double const earProb = 0.5;
double const shellProb = 0.5;
double const camoProb = 0.5;
double const finProb = 0.5;
const std::array<double, 4> behaviourDistrib{
        {0.25, 0.25, 0.25, 0.25}}; // [probGregarious, probFearful, probKamikaze, probMultiple]

#endif //AQUARIUM_CONSTANTS_H
