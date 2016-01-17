// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_WORLD_H
#define INC_3DE_WORLD_H

#include <string>
#include <vector>

#include "vertex.h"
#include "sector.h"
#include "player.h"

class World {

public:
    void load(std::string const &filename);

    Player get_player() const;
    std::vector<Sector> get_sectors() const;

private:
    void add_sector(std::istringstream &ss, std::vector<Vertex> const &vertices) noexcept;
    void add_vertices(std::istringstream &ss, std::vector<Vertex> &v);
    Player create_player(std::istringstream &ss) const;

    Player player;
    std::vector<Sector> sectors;
};


#endif //INC_3DE_WORLD_H
