// MIT License, (C)2016
// Created by jacob on 1/18/16.
//

#include "scene.h"
#include <algorithm>

Scene::Scene(World const &world)
: player{world.get_player()}, sectors{world.get_sectors()} {

}

void Scene::initialize() {
    surface = SDL_SetVideoMode(608, 480, 32, 0);

    SDL_EnableKeyRepeat(150, 30);

    SDL_ShowCursor(SDL_DISABLE);
}

void Scene::game_loop() {
    bool move_forward = false;
    bool move_backward = false;
    bool strafe_left = false;
    bool strafe_right = false;

    while (true) {
        SDL_LockSurface(surface);
        draw();
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

        player.set_ground();
        player.fall();
        player.walk(sectors);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            move_forward = event.type == SDL_KEYDOWN;
                            break;
                        case SDLK_a:
                            strafe_left = event.type == SDL_KEYDOWN;
                            break;
                        case SDLK_s:
                            move_backward = event.type == SDL_KEYDOWN;
                            break;
                        case SDLK_d:
                            strafe_right = event.type == SDL_KEYDOWN;
                            break;
                        case SDLK_SPACE:
                            player.jump();
                            break;
                        case SDLK_LCTRL:
                        case SDLK_RCTRL:
                            player.duck(event.type == SDL_KEYDOWN);
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case SDL_QUIT:
                    return;
            }
        }

        int x, y;
        SDL_GetRelativeMouseState(&x, &y);
        player.calculate_angle(x, y);
        player.move(0, 0, sectors);

        player.calculate_move(move_forward, strafe_left, move_backward, strafe_right);

        SDL_Delay(10);
    }
}

void Scene::quit() {
    SDL_Quit();
}

void Scene::draw() {

}

