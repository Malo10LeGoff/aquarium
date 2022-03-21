#include <random>
#include <iterator>
#include "../src/constants.h"


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
    double std = (maxSpeedShell - mean) / 2;
    std::normal_distribution<double> shellSpeed (mean, std);

    return clip(shellSpeed(mt), 0 , 1);
}

double randomShellDeathCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minDeathCoefShell - maxDeathCoefShell) / 2;
    // std so that 95% are between min and max
    double std = (maxDeathCoefShell - mean) / 2;
    std::normal_distribution<double> shellDeath (mean, std);

    return clip(shellDeath(mt), 0, 1);
}

double randomCamoCoef() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minCamoCoefCamo - maxCamoCoefCamo) / 2;
    // std so that 95% are between min and max
    double std = (maxCamoCoefCamo - mean) / 2;
    std::normal_distribution<double> camoCoef (mean, std);

    return clip(camoCoef(mt), minCamoCoefCamo, maxCamoCoefCamo);
}
double randomSpeedCoefFins() {
    std::random_device rd;
    std::mt19937 mt(rd());
    double mean = (minSpeedFins - maxSpeedFins) / 2;
    // std so that 95% are between min and max
    double std = (maxSpeedFins - mean) / 2;
    std::normal_distribution<double> finSpeed (mean, std);

    return finSpeed(mt);
}