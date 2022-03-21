#include <random>
#include <iterator>
#include "../src/constants.h"
#include "Vector.h"

template <typename RandomGenerator = std::default_random_engine>
struct random_selector
{
    //On most platforms, you probably want to use std::random_device("/dev/urandom")()
    random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
            : gen(g) {}

    template <typename Iter>
    Iter select(Iter start, Iter end) {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(gen));
        return start;
    }

    //convenience function
    template <typename Iter>
    Iter operator()(Iter start, Iter end) {
        return select(start, end);
    }

    //convenience function that works on anything with a sensible begin() and end(), and returns with a ref to the value type
    template <typename Container>
    auto operator()(const Container& c) -> decltype(*begin(c))& {
        return *select(begin(c), end(c));
    }

private:
    RandomGenerator gen;
};

// Parameter sampling functions
double clip(double value, double lower, double higher) {
    return std::max(lower, std::min(higher, value));
}
double randomShellSpeedCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minSpeedShell - maxSpeedShell) / 2;
    // std so that 95% are between min and max
    double stddev = (maxSpeedShell - mean) / 2;
    std::normal_distribution<double> shellSpeed (mean, stddev);

    return clip(shellSpeed(mt), 0 , 1);
}

double randomShellDeathCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minDeathCoefShell - maxDeathCoefShell) / 2;
    // std so that 95% are between min and max
    double stddev = (maxDeathCoefShell - mean) / 2;
    std::normal_distribution<double> shellDeath (mean, stddev);

    return clip(shellDeath(mt), 0, 1);
}

double randomCamoCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minCamoCoefCamo - maxCamoCoefCamo) / 2;
    // std so that 95% are between min and max
    double stddev = (maxCamoCoefCamo - mean) / 2;
    std::normal_distribution<double> camoCoef (mean, stddev);

    return clip(camoCoef(mt), minCamoCoefCamo, maxCamoCoefCamo);
}
double randomSpeedCoefFins() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minSpeedFins - maxSpeedFins) / 2;
    // std so that 95% are between min and max
    double stddev = (maxSpeedFins - mean) / 2;
    std::normal_distribution<double> finSpeed (mean, stddev);

    return finSpeed(mt);
}

Vector randomPosition() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> y (0 , screenHeightPX);
    std::uniform_int_distribution<> x (0, screenWidthPX);

    return Vector (y(mt), x(mt));
}

Vector randomSpeed() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double stddev = 0.25 * baseSpeed;
    std::normal_distribution<> speed (baseSpeed, stddev);
    std::uniform_real_distribution<> radian (0, 2 * M_PI);
    return speed(mt) * Vector(1,0).rotate(radian(mt));
}