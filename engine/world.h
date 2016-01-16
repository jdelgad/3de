// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_WORLD_H
#define INC_3DE_WORLD_H

#include <string>

class World {

public:
    void load(std::string const &filename);

    int getPlayer() const;
    int getSector()  const;
    int getVertex() const;

private:
    int player = 0;
    int sector = 0;
    int vertex = 0;
};


#endif //INC_3DE_WORLD_H
