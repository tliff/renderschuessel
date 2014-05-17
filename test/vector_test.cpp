#include "gtest/gtest.h"
#include "renderschuessel.hpp"
#include "math.hpp"

TEST(VectorTest, Length) {
    Vector3 v = {3,1.5,-2};
    EXPECT_DOUBLE_EQ(v.length(), sqrt(15.25));
    v.normalize();
    EXPECT_DOUBLE_EQ(v.length(), 1);
}

TEST(VectorTest, Norm) {
    Vector3 v = {1,2,3};
    Vector3 w = {2,4,6};
    v.normalize();
    EXPECT_EQ(v, w.norm());
}

TEST(VectorTest, CrossProduct) {
    Vector3 x = {7,2,-9};
    Vector3 y = {2,3.5,18};
    Vector3 z = {67.5,-144,20.5};
    EXPECT_EQ(x%y,z);
    
}