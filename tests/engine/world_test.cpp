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

    std::vector<Sector> sectors = w.get_sectors();
    std::vector<Vertex> vertices = w.get_vertices();
    std::vector<Vertex> sv = sectors[0].get_vertices();

    EXPECT_EQ(1, w.get_player());
    EXPECT_EQ(25, static_cast<int>(sectors.size()));
    EXPECT_EQ(54, static_cast<int>(vertices.size()));


    EXPECT_EQ(1, sv[0].getX());
    EXPECT_EQ(2, sv[0].getY());
    EXPECT_EQ(5, sv[1].getX());
    EXPECT_EQ(7, sv[1].getY());
    EXPECT_EQ(5, sv[2].getX());
    EXPECT_EQ(11, sv[2].getY());
    EXPECT_EQ(1, sv[3].getX());
    EXPECT_EQ(16, sv[3].getY());
}

TEST(WorldTest, LoadInvalidData) {
    World w;
    EXPECT_THROW(w.load("../data/map-invaliddata.txt"), std::runtime_error);
}