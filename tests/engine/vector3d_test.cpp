// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "vector3d.h"

TEST(Vector3dTest, CrossProduct) {
    Vector3D<int> v1{3,-3,1};
    Vector3D<int> v2{4,9,2};
    Vector3D<int> result = v1.cross_product(v2);

    EXPECT_EQ(-15, result.getX());
    EXPECT_EQ(-2, result.getY());
    EXPECT_EQ(39, result.getZ());
}

TEST(Vector3dTest, CrossProductReturnsZeroVector) {
    Vector3D<int> v1{3,-3,1};
    Vector3D<int> v2{-12,12,-4};
    Vector3D<int> result = v1.cross_product(v2);

    EXPECT_EQ(0, result.getX());
    EXPECT_EQ(0, result.getY());
    EXPECT_EQ(0, result.getZ());
}

TEST(Vector3dTest, CrossProductIn2D) {
    Vector3D<int> v1{3,-3,0};
    Vector3D<int> v2{4,9,0};
    Vector3D<int> result = v1.cross_product(v2);

    EXPECT_EQ(0, result.getX());
    EXPECT_EQ(0, result.getY());
    EXPECT_EQ(39, result.getZ());
}