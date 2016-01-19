// MIT License, (C)2016
// Created by jacob on 1/18/16.
//

#include "scene.h"
#include <algorithm>
#include <bitset>

const float DUCK_HEIGHT = 2.5;
const float EYE_HEIGHT = 6;
const float GRAVITY = -0.05f;
const float HEAD_MARGIN = 1;
const float KNEE_HEIGHT = 2;

// clamp value into set range
float clamp(float a, float mi, float ma) {
    return std::min(std::max(a,mi), ma);
}

// local functions specific to this cpp implementation
bool overlap(float a0, float a1, float b0, float b1) {
    return std::min(a0, a1) <= std::max(b0, b1) && std::min(b0, b1) <= std::max(a0, a1);
}

// the cross product of 2 vectors on the xz-plane is only on the z-axis
// which is a scalar
float pointside(float px, float py, float x0, float y0, float x1, float y1) {
    Vector3D<float> v1{x1-x0, y1-y0, 0};
    Vector3D<float> v2{px-x0, py-y0, 0};
    Vector3D<float> cross_product = v1.cross_product(v2);
    return cross_product.getZ();
}

bool intersect(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
    return overlap(x0, x1, x2, x3) && overlap(y0, y1, y2, y3);
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
    // not an stl vector, may replace with std::bitset
    std::vector<bool> wsad{false, false, false, false};
    float yaw = 0;

    while (true) {
        SDL_LockSurface(surface);
        draw();
        SDL_UnlockSurface(surface);
        SDL_Flip(surface);

        detect_vertical_collision();
        detect_horizontal_collision();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_w: {
                            wsad[0] = event.type == SDL_KEYDOWN;
                            break;
                        }
                        case SDLK_s: {
                            wsad[1] = event.type == SDL_KEYDOWN;
                            break;
                        }
                        case SDLK_a: {
                            wsad[2] = event.type == SDL_KEYDOWN;
                            break;
                        }
                        case SDLK_d: {
                            wsad[3] = event.type == SDL_KEYDOWN;
                            break;
                        }
                        case SDLK_SPACE: {
                            if (ground) {
                                player.get_velocity().setZ(player.get_velocity().getZ() + 0.5);
                                falling = true;
                            }
                        }
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
        if (wsad[0]) {
            move_vector[0] += player.get_angle_cos() * 0.2f;
            move_vector[1] += player.get_angle_sin() * 0.2f;
        }
        if (wsad[1]) {
            move_vector[0] -= player.get_angle_cos() * 0.2f;
            move_vector[1] -= player.get_angle_sin() * 0.2f;
        }
        if (wsad[2]) {
            move_vector[0] += player.get_angle_cos() * 0.2f;
            move_vector[1] -= player.get_angle_sin() * 0.2f;
        }
        if (wsad[3]) {
            move_vector[0] -= player.get_angle_cos() * 0.2f;
            move_vector[1] += player.get_angle_sin() * 0.2f;
        }

        bool pushing = wsad[0] || wsad[1] || wsad[2] || wsad[3];
        float acceleration = pushing ? 0.4 : 0.2;
        Vector3D<float> velocity = player.get_velocity();
        velocity.setX(velocity.getX() * (1 - acceleration) + move_vector[0] * acceleration);
        velocity.setY(velocity.getY() * (1-acceleration) + move_vector[1] * acceleration);

        if (pushing) {
            moving = true;
        }

        SDL_Delay(10);
    }
}

void Scene::quit() {
    SDL_Quit();
}

void Scene::draw() {

}

void Scene::detect_vertical_collision() {

    ground = !falling;

    if (!falling) {
        return;
    }

    player.get_velocity().setZ(player.get_velocity().getZ() - GRAVITY);

    Vector3D<float> location = player.get_location();
    Vector3D<float> velocity = player.get_velocity();

    float next_player_z = location.getZ() + player.get_velocity().getZ();
    if (player.get_velocity().getZ() < 0 &&
                next_player_z < player.get_sector().get_floor() + EYE_HEIGHT) {
        location.setZ(player.get_sector().get_floor() + EYE_HEIGHT);
        velocity.setZ(0);
        falling = false;
        ground = true;
    } else if (velocity.getZ() > 0 &&
               next_player_z > player.get_sector().get_ceiling()) {
        velocity.setZ(0);
        falling = true;
    }

    if (falling) {
        location.setZ(location.getZ() + velocity.getZ());
        moving = true;
    }

    player.set_location(location);
    player.set_velocity(velocity);
}

void Scene::detect_horizontal_collision() {

    if (!moving) {
        return;
    }

    Vector3D<float> location = player.get_location();
    Vector3D<float> velocity = player.get_velocity();

    float dx = velocity.getX();
    float dy = velocity.getY();

    for (int i = 0; i < player.get_sector().get_number_of_points(); i++) {
        if (intersect(location.getX(), location.getY(),
                      location.getX()+velocity.getX(), location.getY() + velocity.getY(),
                      player.get_sector().get_vertices()[i].getX(), player.get_sector().get_vertices()[i].getY(),
                      player.get_sector().get_vertices()[i+1].getX(), player.get_sector().get_vertices()[i+1].getY()) &&
                pointside(location.getX()+velocity.getX(), location.getY()+velocity.getY(),
                          player.get_sector().get_vertices()[i].getX(), player.get_sector().get_vertices()[i].getY(),
                          player.get_sector().get_vertices()[i+1].getX(), player.get_sector().get_vertices()[i+1].getY())) {

            // check where the hole is??
            float hole_low = player.get_sector().get_neighbors()[i] < 0 ? 9e9 : std::max(player.get_sector().get_floor(), sectors[player.get_sector().get_neighbors()[i]].get_floor());
            float hole_high = player.get_sector().get_neighbors()[i] < 0 ? 9e9 : std::min(player.get_sector().get_ceiling(), sectors[player.get_sector().get_neighbors()[i]].get_ceiling());

            if (hole_high < location.getZ() + HEAD_MARGIN ||
                    hole_low > location.getZ() - EYE_HEIGHT + KNEE_HEIGHT) {
                // bumps into a wall. slide along the wall
                // from Wikipedia's "vector projection"
                float xd = player.get_sector().get_vertices()[i+1].getX() - player.get_sector().get_vertices()[i].getX();
                float yd = player.get_sector().get_vertices()[i+1].getY() - player.get_sector().get_vertices()[i].getY();
                dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
                dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
                moving = false;
            }
        }
    }

    player.move(dx, dy, sectors);
    falling = true;
}
