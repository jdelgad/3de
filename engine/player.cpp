// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "player.h"

#include <algorithm>
#include <iostream>

const float EYE_HEIGHT = 6;
const float GRAVITY = -0.05f;
const float HEAD_MARGIN = 1;
const float KNEE_HEIGHT = 2;

// clamp value into set range
float clamp(float a, float b, float c) {
    return std::min(std::max(a,b), c);
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

Player::Player()
: Player{Vector3D<float>{0,0,0}, 0, Sector{}} {

}

Player::Player(Vector3D<float> const &location, float angle, Sector const &sector)
: location{location}, velocity{0, 0, 0}, angle{angle}, yaw{0}, sector{sector} {

    this->location.setZ(location.getZ() + EYE_HEIGHT);
}

Sector Player::get_sector() const {
    return sector;
}

float Player::get_angle() const {
    return angle;
}

Vector3D<float> Player::get_velocity() const {
    return velocity;
}

void Player::set_angle(float angle) noexcept {
    this->angle = angle;
}

Vector3D<float> Player::get_location() const {
    return location;
}

void Player::move(float dx, float dy, std::vector<Sector> const &sectors) {
    float px = location.getX();
    float py = location.getY();

    // check if this movement has the player cross into another sector
    // Since the edge vertices of each sector are defined in clock-wise order,
    // pointside will aways return -1 for a point that is outside the sector
    // and 0 or 1 for a point that is inside
    for (int i = 0; i < sector.get_number_of_points(); i++) {
        const Vertex current_vertex = sector.get_vertices()[i];
        const Vertex next_vertex = sector.get_vertices()[i+1];
        if (sector.get_neighbors()[i] >= 0 &&
                intersect(px, py,
                          px+dx, py+dy,
                          current_vertex.getX(), current_vertex.getY(),
                          next_vertex.getX(), next_vertex.getY()) &&
                pointside(px+dx, py+dy,
                          current_vertex.getX(), current_vertex.getY(),
                          next_vertex.getX(), next_vertex.getY()) < 0) {
            sector = sectors[sector.get_neighbors()[i]];
            break;
        }
    }

    location.setX(location.getX() + dx);
    location.setY(location.getY() + dy);
}

float Player::get_angle_cos() const {
    return std::cos(angle);
}

float Player::get_angle_sin() const {
    return std::sin(angle);
}

void Player::fall() {
    if (!falling) {
        return;
    }

    velocity.setZ(get_velocity().getZ() - GRAVITY);

    float next_player_z = location.getZ() + velocity.getZ();
    if (velocity.getZ() < 0 &&
        next_player_z < sector.get_floor() + EYE_HEIGHT) {
        location.setZ(sector.get_floor() + EYE_HEIGHT);
        velocity.setZ(0);
        falling = false;
        ground = true;
    } else if (velocity.getZ() > 0 &&
               next_player_z > sector.get_ceiling()) {
        velocity.setZ(0);
        falling = true;
    }

    if (falling) {
        location.setZ(location.getZ() + velocity.getZ());
        moving = true;
    }

}

void Player::walk(std::vector<Sector> const &sectors) {

    if (!moving) {
        return;
    }

    float dx = velocity.getX();
    float dy = velocity.getY();

    for (int i = 0; i < sector.get_number_of_points(); i++) {
        if (intersect(location.getX(), location.getY(),
                      location.getX()+velocity.getX(), location.getY() + velocity.getY(),
                      sector.get_vertices()[i].getX(), sector.get_vertices()[i].getY(),
                      sector.get_vertices()[i+1].getX(), sector.get_vertices()[i+1].getY()) &&
            pointside(location.getX()+velocity.getX(), location.getY()+velocity.getY(),
                      sector.get_vertices()[i].getX(), sector.get_vertices()[i].getY(),
                      sector.get_vertices()[i+1].getX(), sector.get_vertices()[i+1].getY())) {

            // check where the hole is??
            float hole_low = sector.get_neighbors()[i] < 0 ? 9e9 : std::max(sector.get_floor(), sectors[sector.get_neighbors()[i]].get_floor());
            float hole_high = sector.get_neighbors()[i] < 0 ? 9e9 : std::min(sector.get_ceiling(), sectors[sector.get_neighbors()[i]].get_ceiling());

            if (hole_high < location.getZ() + HEAD_MARGIN ||
                hole_low > location.getZ() - EYE_HEIGHT + KNEE_HEIGHT) {
                // bumps into a wall. slide along the wall
                // from Wikipedia's "vector projection"
                float xd = sector.get_vertices()[i+1].getX() - sector.get_vertices()[i].getX();
                float yd = sector.get_vertices()[i+1].getY() - sector.get_vertices()[i].getY();
                dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
                dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
                moving = false;
            }
        }
    }

    move(dx, dy, sectors);
    falling = true;
}

void Player::set_moving(bool moving) noexcept {
    this->moving = moving;
}

void Player::jump() {
    if (ground) {
        location.setZ(velocity.getZ() + 0.5f);
        falling = true;
    }
}

void Player::set_ground() noexcept {
    ground = !falling;
}

void Player::duck(bool ducking) noexcept {
    this->ducking = ducking;
    falling = true;
}

void Player::move_forward(std::vector<float> &move_vector) noexcept {
    move_vector[0] += get_angle_cos() * 0.2f;
    move_vector[1] += get_angle_sin() * 0.2f;
}

void Player::move_left(std::vector<float> &move_vector) noexcept {
    move_vector[0] += get_angle_sin() * 0.2f;
    move_vector[1] -= get_angle_cos() * 0.2f;
}

void Player::move_right(std::vector<float> &move_vector) noexcept {
    move_vector[0] -= get_angle_sin() * 0.2f;
    move_vector[1] += get_angle_cos() * 0.2f;
}

void Player::move_backward(std::vector<float> &move_vector) noexcept {
    move_vector[0] -= get_angle_cos() * 0.2f;
    move_vector[1] -= get_angle_sin() * 0.2f;
}

void Player::calculate_angle(int x, int y) {
    angle += x * 0.03f;
    delta = clamp(delta - y * 0.05f, -5, 5);
    yaw = delta - velocity.getZ() * 0.5f;
    std::cout << delta << " " << yaw << std::endl;
}

void Player::calculate_move(bool forward, bool left, bool backward, bool right) {
    std::vector<float> move_vector{0, 0};
    if (forward) {
        move_forward(move_vector);
    }
    if (left) {
        move_left(move_vector);
    }
    if (backward) {
        move_backward(move_vector);
    }
    if (right) {
        move_right(move_vector);
    }

    bool key_pressed = forward || backward || left || right;
    float acceleration = key_pressed ? 0.4f : 0.2f;

    velocity.setX(velocity.getX() * (1 - acceleration) + move_vector[0] * acceleration);
    velocity.setY(velocity.getY() * (1 - acceleration) + move_vector[1] * acceleration);

    set_moving(key_pressed);
}

void Player::set_velocity(Vector3D<float> const &velocity) noexcept {
    this->velocity = velocity;
}

float Player::get_yaw() const {
    return yaw;
}

void Player::set_yaw(float yaw) noexcept {
    this->yaw = yaw;
}
