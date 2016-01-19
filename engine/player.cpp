// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "player.h"

#include <algorithm>

const int EYE_HEIGHT = 6;

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
: location{location}, velocity{0, 0, 0}, angle{angle}, angle_sin{0}, angle_cos{0}, yaw{0}, sector{sector} {

    this->location.setZ(location.getZ() + EYE_HEIGHT);
}

void Player::set_velocity(Vector3D<float> const &velocity) noexcept {
    this->velocity = velocity;
}

void Player::set_sector(Sector const &sector) noexcept {
    this->sector = sector;
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

void Player::set_location(Vector3D<float> const &l) noexcept {
    this->location = l;
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

void Player::set_yaw(float yaw) noexcept {
    this->yaw = yaw;
}

float Player::get_angle_cos() const {
    return std::cos(angle);
}

float Player::get_angle_sin() const {
    return std::sin(angle);
}
