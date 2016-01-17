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
    vertices.clear();
    sectors.clear();
    player = 0;
    while (std::getline(map, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "vertex") {
            add_vertices(ss);
        } else if (type == "sector") {
            add_sector(ss);
        } else if (type == "player") {
            player++;
        } else {
            throw std::runtime_error("Could not load map. Invalid data format found in " + filename);
        }
    }

    map.close();
}

int World::get_player() const {
    return player;
}

std::vector<Sector> World::get_sectors() const {
    return sectors;
}

std::vector<Vertex> World::get_vertices() const {
    return vertices;
}

void World::add_vertices(std::istringstream &ss) {
    float y = 0;
    ss >> y;

    float x = 0;
    while (ss >> x) {
        vertices.emplace_back(Vertex{x, y});
    }
}

void World::add_sector(std::istringstream &ss) {
    float floor = 0;
    float ceiling = 0;
    ss >> floor;
    ss >> ceiling;
    Sector s(floor, ceiling);

    int data = 0;
    std::vector<int> points;
    while (ss >> data) {
        points.push_back(data);
        //std::cout << "pushing back: " << data << std::endl;
    }

    //std::cout << "number of points = " << points.size() << std::endl;
    int m = static_cast<int>(points.size()) / 2;
    //std::cout << "npoints = " << m << std::endl;
    s.set_number_of_points(m);
    for (int n = 0; n < m; n++) {
        //std::cout << "num[m+n] = num[" << m+n << "] = " << points[m+n] << std::endl;
        s.add_neighbor(points[n+m]);
        s.add_vertex(vertices[points[n]]);
        //std::cout << "vertex[n+1] = vertex[" << n+1 << "] = vert[num[n]] = vert[" << points[n] << "]" << std::endl;
    }

    s.add_vertex(vertices[0]);
    sectors.push_back(s);
}
