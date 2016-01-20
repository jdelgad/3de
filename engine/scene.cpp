// MIT License, (C)2016
// Created by jacob on 1/18/16.
//

#include "scene.h"
#include <algorithm>

// clamp value into set range
float clamp(float a, float mi, float ma) {
    return std::min(std::max(a,mi), ma);
}

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
    bool strafe_right;

    float yaw = 0;

    while (true) {
        SDL_LockSurface(surface);
        draw();
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

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
        player.set_angle(player.get_angle() + x * 0.03f);
        yaw = clamp(yaw - y * 0.05f, -5, -5);
        player.set_yaw(yaw - player.get_velocity().getZ() * 0.5f);
        player.move(0, 0, sectors);

        std::vector<float> move_vector{0, 0};
        if (move_forward) {
            player.move_forward(move_vector);
        }
        if (strafe_left) {
            player.move_backward(move_vector);
        }
        if (move_backward) {
            player.move_left(move_vector);
        }
        if (strafe_right) {
            player.move_right(move_vector);
        }

        bool key_pressed = move_forward || move_backward || strafe_left || strafe_right;
        float acceleration = key_pressed ? 0.4f : 0.2f;
        Vector3D<float> velocity = player.get_velocity();
        velocity.setX(velocity.getX() * (1 - acceleration) + move_vector[0] * acceleration);
        velocity.setY(velocity.getY() * (1-acceleration) + move_vector[1] * acceleration);

        if (key_pressed) {
            player.set_moving(true);
        }

        SDL_Delay(10);
    }
}

void Scene::quit() {
    SDL_Quit();
}

void Scene::draw() {

}

