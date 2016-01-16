// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "world.h"

TEST(WorldTest, LoadNoSuchFile) {
    World w;
    EXPECT_THROW(w.load("nosuchfile"), std::runtime_error);
}

TEST(WorldTest, LoadFileSuccess) {
    World w;
    EXPECT_NO_THROW(w.load("../data/map-clear.txt"));

    EXPECT_EQ(1, w.getPlayer());
    EXPECT_EQ(25, w.getSector());
    EXPECT_EQ(12, w.getVertex());

}