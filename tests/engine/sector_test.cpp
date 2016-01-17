// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "sector.h"

TEST(SectorTest, DefaultCtor) {
    Sector s;
    EXPECT_EQ(0, s.get_ceiling());
    EXPECT_EQ(0, s.get_floor());
}

TEST(SectorTest, FloorCeilingCtor) {
    Sector s{3,5.5};
    EXPECT_EQ(3, s.get_floor());
    EXPECT_EQ(5.5, s.get_ceiling());
}

TEST(SectorTest, TestNumberOfPoints) {
    Sector s;
    int n = 5;
    s.set_number_of_points(n);
    EXPECT_EQ(n, s.get_number_of_points());
}

TEST(SectorTest, AddNeighbors) {
    Sector s;
    s.add_neighbor(1);
    s.add_neighbor(20);
    std::vector<int> v = s.get_neighbors();
    EXPECT_EQ(2, static_cast<int>(v.size()));
    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(20, v[1]);
}

TEST(SectorTest, AddVertex) {
    Sector s;
    Vertex v1{1,2};
    s.add_vertex(v1);
    Vertex v2{3,4};
    s.add_vertex(v2);
    std::vector<Vertex> vertices = s.get_vertices();
    EXPECT_EQ(2, static_cast<int>(vertices.size()));
    EXPECT_TRUE(vertices.at(0) == v1);
    EXPECT_TRUE(vertices.at(1) == v2);
}