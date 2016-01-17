// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_WORLD_H
#define INC_3DE_WORLD_H

#include <string>
#include <vector>

#include "vertex.h"
#include "sector.h"

class World {

public:
    void load(std::string const &filename);

    int get_player() const;
    std::vector<Sector> get_sectors() const;

private:
    void add_sector(std::istringstream &ss, std::vector<Vertex> const &vertices);
    void add_vertices(std::istringstream &ss, std::vector<Vertex> &v);

    int player = 0;
    std::vector<Sector> sectors;
};


#endif //INC_3DE_WORLD_H
