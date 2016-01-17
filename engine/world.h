// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_WORLD_H
#define INC_3DE_WORLD_H

#include <string>
#include <vector>

#include "vertex.h"

class World {

public:
    void load(std::string const &filename);

    int getPlayer() const;
    int getSector()  const;
    unsigned long get_number_of_vertices() const;

private:
    void addVertices(std::istringstream &ss);

    std::vector<Vertex> vertices;
    int player = 0;
    int sector = 0;
};


#endif //INC_3DE_WORLD_H
