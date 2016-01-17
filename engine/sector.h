// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_SECTOR_H
#define INC_3DE_SECTOR_H

#include <vector>

#include "vertex.h"

class Sector {
public:
    Sector();
    Sector(float floor, float ceiling);

    float get_floor() const;
    float get_ceiling() const;

    int get_number_of_points() const;
    void set_number_of_points(int points) noexcept;

    void add_neighbor(int neighbor) noexcept;
    std::vector<int> get_neighbors() const;

    void add_vertex(Vertex const &v) noexcept;
    std::vector<Vertex> get_vertices() const;

private:
    float floor;
    float ceiling;
    int number_of_points;
    std::vector<int> neighbors;
    std::vector<Vertex> vertices;
};


#endif //INC_3DE_SECTOR_H
