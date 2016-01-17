// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "player.h"

const int EyeHeight = 6;

Player::Player()
: Player{Vector3D<float>{0,0,0}, 0, 0} {

}

Player::Player(Vector3D<float> const &location, float angle, int sector)
: location{location}, velocity{0, 0, 0}, angle{angle}, angle_sin{0}, angle_cos{0}, yaw{0}, sector{sector} {

    this->location.setZ(location.getZ() + EyeHeight);
}

void Player::set_velocity(Vector3D<float> const &velocity) noexcept {
    this->velocity = velocity;
}

void Player::set_sector(int sector) noexcept {
    this->sector = sector;
}

int Player::get_sector() const {
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
