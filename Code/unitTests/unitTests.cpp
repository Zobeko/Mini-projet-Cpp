#include <gtest/gtest.h>
#include "PickUp.h"
#include "Unite.h"


namespace myNameSpace {

TEST(TestCreationUnite, TestIntersectPickUp) {
    std::map<std::string, sf::Texture> textDictionnary;

    PickUp pickupTest(0,0,32,32,"Pierre.png",textDictionnary);
    Unite UniteTest1(10, 0, 32, 32, "Pierre.png", textDictionnary);
    Unite UniteTest2(100, 0, 32, 32, "Pierre.png", textDictionnary);

    EXPECT_TRUE(pickupTest.intersect(UniteTest1));
    EXPECT_FALSE(pickupTest.intersect(UniteTest2));
    EXPECT_EQ(1,1);
}

}
