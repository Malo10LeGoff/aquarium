#include "gtest/gtest.h"
#include "../src/Behaviour.h"
#include <iostream>

// Gregarious Behaviour
class TestGregariousBehaviour : public ::testing::Test {
protected:
    void SetUp() override {


    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {{{1 , 1}, {1,1} }};
    GregariousBehaviour b = GregariousBehaviour();
    std::array<float,2> coordinates {0,0};
};

TEST_F(TestGregariousBehaviour, TestInit) {
    auto ret = b.moveDirection(creatureCoordinates , visibleCreatures);
    // check for colinearity
    EXPECT_EQ(0, visibleCreatures[0][0][0] * ret[1] - visibleCreatures[0][0][1] * ret[0]);
    std::cout << "direction followed\n" << "x:" << ret[0] <<"\ny:" <<  ret[1] << "\n";

}

TEST_F(TestGregariousBehaviour, TestFollowsAverage) {
    visibleCreatures.push_back(std::array<std::array<float,2>,2>{{{2 , -1}, {0,0} }});
std::array<float,2> expectedDirection {0,0};
    //std::cout << "visibleCreatures size " << visibleCreatures.size() << "\n";
    for (auto it = std::begin(visibleCreatures); it != std::end(visibleCreatures); ++it) {
        //std::cout << " x_move " << (*it)[0][0] << " y_move " << (*it)[0][1] << "\n";
        expectedDirection[0] += (*it)[0][0];
        expectedDirection[1] += (*it)[0][1];
    }
    auto ret = b.moveDirection(std::array<float,2>{0,0} , visibleCreatures);
    // check for colinearity
    EXPECT_EQ(0, expectedDirection[0] * ret[1] - expectedDirection[1] *ret[0] );
    std::cout << "direction followed :\n" << "x:" << ret[0] <<"\ny:" <<  ret[1] << "\n";
}

TEST_F(TestGregariousBehaviour, TestSpeedCoef) {
    EXPECT_EQ(1, b.moveSpeedMultiplier(visibleCreatures));
}

// FearfulBehaviour
class TestFearfulBehaviour : public ::testing::Test {
protected:
    void SetUp() override {
    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {{{1 , 1}, {1,1} }};
    FearfulBehaviour b_default = FearfulBehaviour();
    int maxNeighbours = 30;
    float moveSpeedMultiplier = 1.3;
    FearfulBehaviour b_custom = FearfulBehaviour(maxNeighbours, moveSpeedMultiplier);
    std::array<float,2> coordinates {0,0};
};
TEST_F(TestFearfulBehaviour, TestDefaultInit) {
    // Speed coef should be 1 if there are not too many creatures around
    for (int i = 0; i<100; ++i){
        float moveSpeedMultiplier = b_default.moveSpeedMultiplier(visibleCreatures);
        if (visibleCreatures.size() > (unsigned)b_default.maxNeighbours() ){
            EXPECT_GT(moveSpeedMultiplier , 1);
        } else {
            EXPECT_EQ(moveSpeedMultiplier, 1);
        }
    }

    // Check
}

TEST_F(TestFearfulBehaviour, TestCustomInit) {
    EXPECT_EQ(maxNeighbours, b_custom.maxNeighbours());
    for (int i = 0; i<100; ++i){
        float moveSpeedMultiplier = b_custom.moveSpeedMultiplier(visibleCreatures);
        if (visibleCreatures.size() > (unsigned)b_custom.maxNeighbours() ){
            EXPECT_GT(moveSpeedMultiplier , moveSpeedMultiplier);
        } else {
            EXPECT_EQ(moveSpeedMultiplier, 1);
        }
    }
}

TEST_F(TestFearfulBehaviour, TestFleeingDirection) {
    // Fill the visible creature vector with all of the same value(the first one)
    while (visiblesCreatures.size() >= (unsigned)b_custom.maxNeighbours()) {
        visibleCreatures.push_back(std::array<float,2>(visibleCreatures[0]));
    }
    std::array<float,2> expectedDirection {0,0};
    for (auto it = std::begin(visibleCreatures); it!= std::end(visibleCreatures); ++it) {
        expectedDirection[0] += (*it)[0][0];
        expectedDirection[1] += (*it)[0][1];
    }
    auto ret = b_custom.moveDirection(creatureCoordinates, visibleCreatures);
    EXPECT_LE(expectedDirection[0] * ret[0] + expectedDirection[1] * ret[1],0);
}