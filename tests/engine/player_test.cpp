// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerTest, InitialPlayer) {
    Vector3D<float> v{1,2,3};

    Player player{v, 10, 20};
    EXPECT_EQ(1, player.get_location().getX());
    EXPECT_EQ(2, player.get_location().getY());
    EXPECT_EQ(3, player.get_location().getZ());

    EXPECT_EQ(10, player.get_angle());
    EXPECT_EQ(20, player.get_sector());
}