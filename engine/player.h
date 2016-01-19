// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_PLAYER_H
#define INC_3DE_PLAYER_H


#include "vector3D.h"
#include "sector.h"

class Player {
public:
    Player();
    Player(Vector3D<float> const &location, float angle, Sector const &sector);

    void set_location(Vector3D<float> const &l) noexcept;
    Vector3D<float> get_location() const;

    void set_velocity(Vector3D<float> const &velocity) noexcept;
    Vector3D<float> get_velocity() const;

    void set_angle(float angle) noexcept;
    float get_angle() const;

    void set_sector(Sector const &sector) noexcept;
    Sector get_sector() const;

    void move(float dx, float dy, std::vector<Sector> const &sectors);

    void set_yaw(float yaw) noexcept;

    float get_angle_cos() const;
    float get_angle_sin() const;

private:
    Vector3D<float> location;
    Vector3D<float> velocity;
    float angle;
    float angle_sin;
    float angle_cos;
    float yaw;
    Sector sector;
};


#endif //INC_3DE_PLAYER_H
