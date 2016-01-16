//
// Created by jacob on 1/16/16.
//

#include "world.h"

#include <fstream>
#include <iostream>
#include <sstream>

void World::load(std::string const &filename) {
    const char SPACE = ' ';

    std::ifstream map;
    map.open(filename, std::fstream::in);

    if (!map.is_open()) {
        throw std::runtime_error(filename + " does not exist");
    }

    std::string line;
    vertex = 0;
    sector = 0;
    player = 0;
    while (getline(map, line)) {
        std::stringstream ss(line);
        std::string type;
        getline(ss, type, SPACE);

        if (type.compare("vertex") == 0) {
            vertex++;
        } else if (type.compare("sector") == 0) {
            sector++;
        } else if (type.compare("player") == 0) {
            player++;
        } else {
            std::cerr << "invalid line = " << line << std::endl;
            throw std::runtime_error("invalid data format");
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

int World::getVertex() const {
    return vertex;
}
