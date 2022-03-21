//
// Created by minhtri on 21/03/2022.
//

#ifndef AQUARIUM_CONSTANTS_H
#define AQUARIUM_CONSTANTS_H
#define _USE_MATH_DEFINES
#include <cmath>
// Display
const int screenWidthPX = 1280;
const int screenHeightPX = 1024;
const double maxDetectionCoef = 0.95;
const double minDetectionCoef = 0;

// Accessories
// All coeficients are multiplicative
//     Shell
const double minSpeedShell = 0.6;
const double maxSpeedShell = 1;
const double minDeathCoefShell = 0.5;
const double maxDeathCoefShell = 1;

//      Camo
const double minCamoCoefCamo = 0;
const double maxCamoCoefCamo = 0.99*maxDetectionCoef ;

//      Fins
const double minSpeedFins = 1;
const double maxSpeedFins = 2;

// Behaviour
//      Fearful
const int maxNeighbours = 10;
const double fleeingSpeed = 1.3;

// Sensors
//      Eyes
const double minDetectionAngleEyes = M_PI /4;
const double maxDetectionAngleEyes = M_PI;
const double minRadiusEyes = 20;
const double maxRadiusEyes = 50;
const double maxDetectionCoefEyes = maxDetectionCoef;
const double minDetectionCoefEyes = 0.2;
//       Ears
const double minRadiusEars = 50;
const double maxRadiusEars = 100;
const double maxDetectionCoefEars = maxDetectionCoef*0.3;
const double minDetectionCoefEars = maxDetectionCoefEyes * 0.0001;

// Creature
const double baseSize = 8 ;
const double baseSpeed = 10;
const double time_delta = 1;
const int baseDyingAge = 100;

#endif //AQUARIUM_CONSTANTS_H
