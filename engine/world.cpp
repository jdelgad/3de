// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "world.h"

#include <fstream>
#include <iostream>
#include <sstream>

const char SPACE = ' ';

void World::load(std::string const &filename) {
    std::ifstream map;
    map.open(filename, std::fstream::in);

    if (!map.is_open()) {
        throw std::runtime_error(filename + " does not exist");
    }

    std::string line;
    vertices.clear();
    sector = 0;
    player = 0;
    while (std::getline(map, line)) {
        std::istringstream ss(line);
        std::string type;
        ss >> type;

        if (type == "vertex") {
            addVertices(ss);
        } else if (type == "sector") {
            sector++;
        } else if (type == "player") {
            player++;
        } else {
            throw std::runtime_error("Could not load map. Invalid data format found in " + filename);
        }
    }

    map.close();
}

int World::getPlayer() const {
    return player;
}

int World::getSector() const {
    return sector;
}

unsigned long World::get_number_of_vertices() const {
    return vertices.size();
}

void World::addVertices(std::istringstream &ss) {
    float y = 0;
    ss >> y;

    float x = 0;
    while (ss >> x) {
        vertices.emplace_back(Vertex{x, y});
    }
}
