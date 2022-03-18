#include "gtest/gtest.h"
#include "../src/Behaviour.h"
#include <iostream>

float scalar_product(std::array<float,2> a, std::array<float,2> b) {
    return a[0] * b[0] + a[1] * b[1];
}
float det(std::array<float,2> a, std::array<float,2> b) {
    return a[0] * b[1] - a[1] * b[0];
}

// Gregarious Behaviour
class TestGregariousBehaviour : public ::testing::Test {
protected:
    void SetUp() override {
        visibleCreatures.push_back(std::array<std::array<float,2>,2>{ {{ 1,1 } , {1,1 }} });
    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {};
    GregariousBehaviour b = GregariousBehaviour();
    std::array<float,2> coordinates {0,0};
};

TEST_F(TestGregariousBehaviour, TestInit) {
    auto ret = b.moveDirection(creatureCoordinates , visibleCreatures);
    // check for colinearity
    EXPECT_EQ(0, det(visibleCreatures[0][0], ret));
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
    EXPECT_EQ(0, det(expectedDirection, ret));
    std::cout << "direction followed :\n" << "x:" << ret[0] <<"\ny:" <<  ret[1] << "\n";
}

TEST_F(TestGregariousBehaviour, TestSpeedCoef) {
    EXPECT_EQ(1, b.moveSpeedMultiplier(visibleCreatures));
}

// FearfulBehaviour
class TestFearfulBehaviour : public ::testing::Test {
protected:
    void SetUp() override {
        visibleCreatures.push_back(std::array<std::array<float,2>,2>{ {{ 1,1 } , {1,1 }} });
    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {};
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
    while (visibleCreatures.size() >= (unsigned)b_custom.maxNeighbours()) {
        visibleCreatures.push_back(std::array<std::array<float,2>,2> { visibleCreatures[0] });
    }
    std::array<float,2> expectedDirection {0,0};
    for (auto it = std::begin(visibleCreatures); it!= std::end(visibleCreatures); ++it) {
        expectedDirection[0] += (*it)[0][0];
        expectedDirection[1] += (*it)[0][1];
    }
    auto ret = b_custom.moveDirection(creatureCoordinates, visibleCreatures);
    EXPECT_LE(scalar_product(expectedDirection, ret ),0);
}

// FearfulBehaviour
class TestKamikazeBehaviour : public ::testing::Test {
protected:
    void SetUp() override {
        visibleCreatures.push_back(std::array<std::array<float,2>,2>{ {{ 1,1 } , {1,1 }} });
    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {};
    KamikazeBehaviour b_default = KamikazeBehaviour();
    float moveSpeedMultiplier = 1.3;
    KamikazeBehaviour b_custom = KamikazeBehaviour(moveSpeedMultiplier);
    std::array<float,2> coordinates {0,0};
};

TEST_F(TestKamikazeBehaviour, TestDirection) {
    auto ret = b_default.moveDirection(coordinates, visibleCreatures);
    std::array<float,2> expectedDirection {0,0};
    // here the list of creatures should be one so we know where the creature is goingto go
    std::cout << "returned direction is : " << "\nx: " << ret[0] << " \ny : " << ret[1] << "\n";
    expectedDirection[0] = visibleCreatures[0][1][0] - coordinates[0];
    expectedDirection[1] = visibleCreatures[0][1][1] - coordinates[1];
    EXPECT_EQ(0, det(ret, expectedDirection));

    // Now add one thats closer
    std::array<std::array<float,2>,2> newCreature { {{1,1} , {-0.5,-0.5}} };
    visibleCreatures.push_back(newCreature);
    ret = b_default.moveDirection(coordinates, visibleCreatures);
    expectedDirection[0] = visibleCreatures[1][1][0] - coordinates[0];
    expectedDirection[1] = visibleCreatures[1][1][1] - coordinates[1];

    EXPECT_EQ(0, det(ret, expectedDirection));
}
class TestMultipleBehaviour : public ::testing::Test {
protected:
    void SetUp() override {
        visibleCreatures.push_back(std::array<std::array<float,2>,2>{ {{ 1,1 } , {1,1 }} });
    }
    std::array<float,2> creatureCoordinates {0,0};
    // visibleCreatures is [ [movedirection, coordinates ], ... ]
    std::vector<std::array<std::array<float,2>,2>> visibleCreatures {};
    KamikazeBehaviour kamikaze_default = KamikazeBehaviour();
    float moveSpeedMultiplier = 1.3;
    KamikazeBehaviour kamikaze_fast = KamikazeBehaviour(moveSpeedMultiplier);
    std::array<float,2> coordinates {0,0};

    MultipleBehaviours multipleBehaviours = MultipleBehaviours(); // empty one
};

TEST_F(TestMultipleBehaviour, TestBehaviourContainers) {
    EXPECT_EQ(multipleBehaviours.size(), 0); // check for emptiness


    // Add one element in
    std::unique_ptr<InterfaceBehaviour> kamikaze = kamikaze_default.clone();
    multipleBehaviours.add(kamikaze);
    EXPECT_EQ(multipleBehaviours.size(), 1); // one element

    // Add another
    std::unique_ptr<InterfaceBehaviour> kamikaze2 = kamikaze_fast.clone();
    multipleBehaviours.add(kamikaze2);
    EXPECT_EQ(multipleBehaviours.size(), 2); // two elements

    // remove the first one
    multipleBehaviours.remove(0);
    EXPECT_EQ(multipleBehaviours.size(), 1); // one element
}