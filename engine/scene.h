// MIT License, (C)2016
// Created by jdelgad on 1/18/16.
//

#ifndef INC_3DE_SCENE_H
#define INC_3DE_SCENE_H


#include "SDL.h"
#include "world.h"

class Scene {
public:
    Scene(World const &world);
    void initialize();
    void game_loop();
    void quit();

private:
    void draw();
    void detect_vertical_collision(int ducking);

    SDL_Surface *surface = nullptr;
    World world;
    bool falling = true;
    bool moving = false;
    bool ducking = false;
    bool ground = false;

};


#endif //INC_3DE_SCENE_H
