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

TEST(TestGregariousBehaviour, TestInit) {
    auto ret = b.moveDirection(std::array<float,2>{0,0} , arr);
    // check for colinearity
    EXPECT_EQ(0, arr[0][0][0] * ret[1] - arr[0][0][1] * ret[0]);
    std::cout << "direction followed\n" << "x:" << ret[0] <<"\ny:" <<  ret[1] << "\n";
}

TEST(TestGregariousBehaviour, TestFollowsAverage) {
    arr.push_back(std::array<std::array<float,2>,2>{{{2 , -1}, {0,0} }});
    std::array<float,2> expectedDirection {3,0};
    auto ret = b.moveDirection(std::array<float,2>{0,0} , arr);
    // check for colinearity
    EXPECT_EQ(0, expectedDirection[0] * ret[1] - expectedDirection[1] *ret[0] );
    std::cout << "direction followed\n" << "x:" << ret[0] <<"\ny:" <<  ret[1] << "\n";
}

TEST(TestGregariousBehaviour, TestSpeedCoef) {
    EXPECT_EQ(1, b.moveSpeedMultiplier(arr));
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
    std::array<float,2> coordinates {0,0};
};
TEST(TestFearfulBehaviour, TestDefaultInit) {
    // Speed coef should be 1 if there are not too many creatures around
    for (int i = 0; i<100; ++i){
        float moveSpeedMultiplier = b_default.moveSpeedMultiplier(visibleCreatures)
        if (std::size(arr) > (unsigned)b_default.maxNeighbours() ){
            EXPECT_GT(moveSpeedMultiplier , 1)
        }
        else {
            EXPECT_EQ(moveSpeedMultiplier, 1)
        }
    }

    // Check
}