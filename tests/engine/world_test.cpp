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
    EXPECT_EQ(25, static_cast<int>(sectors.size()));

    std::vector<Vertex> sv = sectors[0].get_vertices();
    EXPECT_EQ(1, sv[0].getX());
    EXPECT_EQ(2, sv[0].getY());
    EXPECT_EQ(5, sv[1].getX());
    EXPECT_EQ(7, sv[1].getY());
    EXPECT_EQ(5, sv[2].getX());
    EXPECT_EQ(11, sv[2].getY());
    EXPECT_EQ(1, sv[3].getX());
    EXPECT_EQ(16, sv[3].getY());

    Player player = w.get_player();
    //EXPECT_EQ(1, player.get_sector());
    EXPECT_EQ(1, player.get_angle());
    Vector3D<float> location = player.get_location();
    EXPECT_EQ(2, location.getX());
    EXPECT_EQ(6, location.getY());
    EXPECT_EQ(6, location.getZ());

    Vector3D<float> velocity = player.get_velocity();
    EXPECT_EQ(0, velocity.getX());
    EXPECT_EQ(0, velocity.getY());
    EXPECT_EQ(0, velocity.getZ());

}

TEST(WorldTest, LoadInvalidData) {
    World w;
    try {
        w.load("../data/map-invaliddata.txt");
        FAIL() << "Expected std::runtime_error";
    } catch (std::runtime_error const &e) {
        EXPECT_EQ(e.what(), std::string("Could not load map. Invalid data format found in ../data/map-invaliddata.txt"));
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(WorldTest, LoadInvalidVertex) {
    World w;
    try {
        w.load("../data/map-invalidvertex.txt");
        FAIL() << "Expected std::runtime_error";
    } catch (std::runtime_error const &e) {
        EXPECT_EQ(e.what(), std::string("Invalid map. Found vertex definition after sector definition."));
    } catch (...) {
        FAIL() << "Expected std::runtime_error";
    }
}