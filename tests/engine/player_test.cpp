// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "player.h"

TEST(PlayerTest, InitialPlayer) {
    Vector3D<float> v{1,2,3};

    Player player{v, 10, Sector{}};
    EXPECT_EQ(1, player.get_location().getX());
    EXPECT_EQ(2, player.get_location().getY());
    EXPECT_EQ(3+6, player.get_location().getZ());

    EXPECT_EQ(10, player.get_angle());
}


// Test case generated from prender.c printf statements
TEST(PlayerTest, MoveCrossedSegment) {
    Vertex vs1{1, 16};
    Vertex vs2{1, 2};
    Vertex vs3{5, 7};

    std::vector<Sector> sectors;
    Sector s1{0, 100};
    s1.set_number_of_points(4);
    s1.add_vertex(vs1);
    s1.add_vertex(vs2);
    s1.add_vertex(vs3);
    s1.add_neighbor(-1);
    s1.add_neighbor(1);
    sectors.push_back(s1);

    float FLOOR = 999;
    float CEILING = 1000;
    Sector s2{FLOOR, CEILING};
    sectors.push_back(s2);

    Vector3D<float> location{4.184440, 6, 0};

    float ANGLE = 30;
    Player player{location, ANGLE, s1};
    float dx = 0.190669;
    float dy = 0;
    player.move(dx, dy, sectors);

    Sector result = player.get_sector();
    EXPECT_EQ(FLOOR, result.get_floor());
    EXPECT_EQ(CEILING, result.get_ceiling());
    EXPECT_EQ(ANGLE, player.get_angle());
    EXPECT_EQ(location.getX()+dx, player.get_location().getX());
    EXPECT_EQ(location.getY()+dy, player.get_location().getY());
}

// Test case generated from prender.c printf statements
TEST(PlayerTest, DidNotCrossSegment) {
    Vertex vs1{1, 16};
    Vertex vs2{1, 2};
    Vertex vs3{5, 7};
    Vertex vs4{5, 11};

    float FLOOR = 999;
    float CEILING = 1000;

    std::vector<Sector> sectors;
    Sector s1{FLOOR, CEILING};
    s1.set_number_of_points(4);
    s1.add_vertex(vs1);
    s1.add_vertex(vs2);
    s1.add_vertex(vs3);
    s1.add_vertex(vs4);
    s1.add_neighbor(-1);
    s1.add_neighbor(1);
    s1.add_neighbor(1);
    s1.add_neighbor(11);
    s1.add_neighbor(22);

    sectors.push_back(s1);


    Vector3D<float> location{4.184440, 6, 0};

    float ANGLE = 25;
    Player player{location, ANGLE, s1};
    EXPECT_NO_FATAL_FAILURE(player.move(0, 0, sectors));

    Sector result = player.get_sector();
    EXPECT_EQ(FLOOR, result.get_floor());
    EXPECT_EQ(CEILING, result.get_ceiling());
    EXPECT_EQ(ANGLE, player.get_angle());
    EXPECT_EQ(location.getX(), player.get_location().getX());
    EXPECT_EQ(location.getY(), player.get_location().getY());
}