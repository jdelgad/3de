// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_PLAYER_H
#define INC_3DE_PLAYER_H


#include "vector3D.h"

class Player {
public:
    Player();
    Player(Vector3D<float> const &location, float angle, int sector);

    void set_location(Vector3D<float> const &l) noexcept;
    Vector3D<float> get_location() const;

    void set_velocity(Vector3D<float> const &velocity) noexcept;
    Vector3D<float> get_velocity() const;

    void set_angle(float angle) noexcept;
    float get_angle() const;

    void set_sector(int sector) noexcept;
    int get_sector() const;

private:
    Vector3D<float> location;
    Vector3D<float> velocity;
    float angle;
    float angle_sin;
    float angle_cos;
    float yaw;
    int sector;
};


#endif //INC_3DE_PLAYER_H
