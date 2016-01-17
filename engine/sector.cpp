// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "sector.h"

Sector::Sector()
: Sector(0, 0) {
}

Sector::Sector(float floor, float ceiling)
: floor{floor}, ceiling{ceiling} {
}

void Sector::set_number_of_points(int points) noexcept {
    number_of_points = points;
}

void Sector::add_neighbor(int neighbor) noexcept {
    neighbors.push_back(neighbor);
}

std::vector<int> Sector::get_neighbors() const {
    return neighbors;
}

float Sector::get_floor() const {
    return floor;
}

float Sector::get_ceiling() const {
    return ceiling;
}

int Sector::get_number_of_points() const {
    return number_of_points;
}

std::vector<Vertex> Sector::get_vertices() const {
    return vertices;
}

void Sector::add_vertex(Vertex const &v) noexcept {
    vertices.push_back(v);
}
