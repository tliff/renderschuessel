#include "gtest/gtest.h"
#include "sphere.hpp"

TEST(SphereTest, Constructor) {
    Sphere s = {{0,0,0},1};
    Ray r = {{-2,0,0},{1,0,0}};
    Intersection i;
    
    Vector3 goal = {-1,0,0};
    
    s.intersect(r,i);
    EXPECT_TRUE(i.point.about(goal));
    EXPECT_TRUE(i.normal.about(goal));
    
    
}