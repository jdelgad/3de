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

TEST(PlayerTest, CalculateMoveForward) {
    bool FORWARD = true;
    Vector3D<float> location{10, 20, 0};
    float ANGLE = 30.f;
    Sector s{};
    Player player{location, ANGLE, s};

    Vector3D<float> velocity{1, 2, 0};
    player.set_velocity(velocity);

    player.calculate_move(FORWARD, false, false, false);
    // velocity.x = 1 * (1 - 0.4) + (cos(30) * 0.2) * 0.4 ~= 0.61234
    EXPECT_FLOAT_EQ(player.get_velocity().getX(), 0.61234);

    // velocity.y = 2 * (1 - 0.4) + (sin(30) * 0.2) * 0.4 ~= 1.12096
    EXPECT_FLOAT_EQ(player.get_velocity().getY(), 1.1209575);
}

TEST(PlayerTest, CalculateMoveBackward) {
    bool BACKWARD = true;
    Vector3D<float> location{10, 20, 0};
    float ANGLE = 30.f;
    Sector s{};
    Player player{location, ANGLE, s};

    Vector3D<float> velocity{100, 200, 0};
    player.set_velocity(velocity);

    player.calculate_move(false, false, BACKWARD, false);
    // velocity.x = 100 * (1 - 0.4) + (-cos(30) * 0.2) * 0.4 ~= 59.9877
    EXPECT_FLOAT_EQ(player.get_velocity().getX(), 59.98766);

    // velocity.y = 200 * (1 - 0.4) + (-sin(30) * 0.2) * 0.4 ~= 120.079
    EXPECT_FLOAT_EQ(player.get_velocity().getY(), 120.07904);
}

TEST(PlayerTest, CalculateMoveLeft) {
    bool LEFT = true;
    Vector3D<float> location{10, 20, 0};
    float ANGLE = 30.f;
    Sector s{};
    Player player{location, ANGLE, s};

    Vector3D<float> velocity{40, 50, 0};
    player.set_velocity(velocity);

    player.calculate_move(false, LEFT, false, false);
    // velocity.x = 40 * (1 - 0.4) + (sin(30) * 0.2) * 0.4 ~= 23.921
    EXPECT_FLOAT_EQ(player.get_velocity().getX(), 23.920958);

    // velocity.y = 50 * (1 - 0.4) + (-cos(30) * 0.2) * 0.4 ~= 29.9877
    EXPECT_FLOAT_EQ(player.get_velocity().getY(), 29.987661);
}

TEST(PlayerTest, CalculateMoveRight) {
    bool RIGHT = true;
    Vector3D<float> location{10, 20, 0};
    float ANGLE = 30.f;
    Sector s{};
    Player player{location, ANGLE, s};

    Vector3D<float> velocity{60, 70, 0};
    player.set_velocity(velocity);

    player.calculate_move(false, false, false, RIGHT);
    // velocity.x = 60 * (1 - 0.4) + (-sin(30) * 0.2) * 0.4 ~= 36.079
    EXPECT_FLOAT_EQ(player.get_velocity().getX(), 36.079044);

    // velocity.y = 70 * (1 - 0.4) + (cos(30) * 0.2) * 0.4 ~= 42.0123
    EXPECT_FLOAT_EQ(player.get_velocity().getY(), 42.012341);
}

TEST(PlayerTest, CalculateViewingAngleAllZeroes) {
    float ANGLE = 0;
    Player player{};
    player.set_angle(ANGLE);

    float YAW = 0;
    player.set_yaw(YAW);

    Vector3D<float> velocity{0, 0, 0};
    player.set_velocity(velocity);

    player.calculate_angle(0, 0);

    EXPECT_FLOAT_EQ(player.get_angle(), 0);

    // player.yaw = min(max(0, -5), 5) - 0 * 0.5f
    EXPECT_FLOAT_EQ(player.get_yaw(), 0);
}