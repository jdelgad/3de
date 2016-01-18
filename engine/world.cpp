// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "world.h"

#include <fstream>
#include <iostream>
#include <sstream>

void World::load(std::string const &filename) {
    std::ifstream map;
    map.open(filename, std::fstream::in);

    if (!map.is_open()) {
        throw std::runtime_error(filename + " does not exist");
    }

    std::string line;
    std::vector<Vertex> vertices;
    sectors.clear();
    while (std::getline(map, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "vertex") {
            add_vertices(ss, vertices);
        } else if (type == "sector") {
            add_sector(ss, vertices);
        } else if (type == "player") {
            player = create_player(ss);
        } else {
            throw std::runtime_error("Could not load map. Invalid data format found in " + filename);
        }
    }

    map.close();
}

Player World::get_player() const {
    return player;
}

std::vector<Sector> World::get_sectors() const {
    return sectors;
}


void World::add_vertices(std::istringstream &ss, std::vector<Vertex> &v) {
    if (sectors.size() != 0) {
        throw std::runtime_error("Invalid map. Found vertex definition after sector definition.");
    }

    float y = 0;
    ss >> y;

    float x = 0;
    while (ss >> x) {
        v.emplace_back(Vertex{x, y});
    }
}

void World::add_sector(std::istringstream &ss, std::vector<Vertex> const &vertices) noexcept {
    float floor = 0;
    float ceiling = 0;
    ss >> floor;
    ss >> ceiling;
    Sector s(floor, ceiling);

    int data = 0;
    std::vector<int> points;
    while (ss >> data) {
        points.push_back(data);
    }

    int m = static_cast<int>(points.size()) / 2;
    s.set_number_of_points(m);
    for (int n = 0; n < m; n++) {
        s.add_neighbor(points[n+m]);
        s.add_vertex(vertices[points[n]]);
    }

    s.add_vertex(vertices[0]);
    sectors.push_back(s);
}

Player World::create_player(std::istringstream &ss) const {
    float x = 0, y = 0;
    ss >> x;
    ss >> y;
    Vector3D<float> location{x, y, 0};

    float angle = 0;
    ss >> angle;

    int sector = 0;
    ss >> sector;

    location.setZ(sectors[sector].get_floor());
    return Player{location, angle, sectors[sector]};
}
