// MIT License, (C)2016
// Created by jacob on 1/18/16.
//

#include "scene.h"

const float DuckHeight = 2.5;
const float EyeHeight = 6;
const float GRAVITY = -0.05f;
Scene::Scene(World const &world)
: world{world} {

}

void Scene::initialize() {
    surface = SDL_SetVideoMode(608, 480, 32, 0);

    SDL_EnableKeyRepeat(150, 30);

    SDL_ShowCursor(SDL_DISABLE);
}

void Scene::game_loop() {
    std::vector<int> wasd{0,0,0,0};

    while (true) {
        SDL_LockSurface(surface);
        draw();
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

        ground = !falling;
        detect_vertical_collision(ducking);
    }
}

void Scene::quit() {
    SDL_Quit();
}

void Scene::draw() {

}

void Scene::detect_vertical_collision(int ducking) {

    ground = !falling;

    if (!falling) {
        return;
    }
    //Vector3D<float> player_velocity = world.get_player().get_velocity();

}
