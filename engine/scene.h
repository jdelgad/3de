// MIT License, (C)2016
// Created by jdelgad on 1/18/16.
//

#ifndef INC_3DE_SCENE_H
#define INC_3DE_SCENE_H


#include "SDL.h"
#include "world.h"
#include "player.h"
#include "sector.h"

class Scene {
public:
    Scene(World const &world);
    void initialize();
    void game_loop();
    void quit();

private:
    void draw();

    Player player;
    std::vector<Sector> sectors;

    SDL_Surface *surface = nullptr;
    World world;
};


#endif //INC_3DE_SCENE_H
