#include "gtest/gtest.h"
#include "../src/Aquarium.h"
#include "../src/Milieu.h"
#include "../src/constants.h"

class TestDetection : public ::testing::Test {
protected:
    void SetUp() override {

    }

    Aquarium ecosysteme = Aquarium(screenWidthPX, screenHeightPX, 30);

};

TEST_F(TestDetection, TestdetectionIsTrue) {

    Creature a = Creature(&ecosysteme.getMilieu());
    Creature b = Creature(&ecosysteme.getMilieu());

    a.setPos(Vector{0, 0});
    a.setSpeed(Vector(1, 0));
    b.setPos(Vector{2, 0});
    b.setSpeed(Vector{0, 0});

    cout << a.getPos() << endl;
    cout << b.getPos() << endl;
    std::unique_ptr<InterfaceSensors> s = std::unique_ptr<Ears>(new Ears(1, 1000));
    a.sensors->add(s);
    EXPECT_EQ(1, a.sensors->sensors_.size());
    bool test = ecosysteme.getMilieu().detect(a, b);


    EXPECT_TRUE(test);

    std::cout << "detectionTest" << "\n";
}