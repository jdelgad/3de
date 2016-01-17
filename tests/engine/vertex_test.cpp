// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "gtest/gtest.h"
#include "vertex.h"

TEST(VertexTest, DefaultCtor) {
    Vertex v;
    EXPECT_EQ(0, v.getX());
    EXPECT_EQ(0, v.getY());
}

TEST(VertexTest, Initialize) {
    Vertex v(1, 2);
    EXPECT_EQ(1, v.getX());
    EXPECT_EQ(2, v.getY());
}

TEST(VertexTest, Equals) {
    Vertex v1(1, 2);
    Vertex v2(1, 2);
    EXPECT_TRUE(v1 == v2);
}

TEST(VertexTest, NotEquals) {
    Vertex v1(1, 2);
    Vertex v2(3, 4);
    EXPECT_FALSE(v1 == v2);
}
