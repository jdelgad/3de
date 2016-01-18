// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_VECTOR3D_H
#define INC_3DE_VECTOR3D_H

template<typename T>
class Vector3D {
public:
    Vector3D(T x, T y, T z);

    Vector3D<T> cross_product(Vector3D<T> const &v) const;

    T getX() const;
    T getY() const;
    T getZ() const;

    void setX(float d);
    void setY(float y);
    void setZ(float d);

private:
    Vector3D();

    T x;
    T y;
    T z;
};

template<typename T>
Vector3D<T>::Vector3D(T x, T y, T z)
        : x{x}, y{y}, z{z}
{
}

template<typename T>
Vector3D<T> Vector3D<T>::cross_product(Vector3D<T> const &v) const {
    T xAns = y * v.z - z * v.y;
    T yAns = z * v.x - x * v.z;
    T zAns = x * v.y - y * v.x;
    return Vector3D{xAns, yAns, zAns};
}

template<typename T>
T Vector3D<T>::getX() const {
    return x;
}

template<typename T>
T Vector3D<T>::getY() const {
    return y;
}

template<typename T>
T Vector3D<T>::getZ() const {
    return z;
}

template<typename T>
void Vector3D<T>::setZ(float z) {
    this->z = z;
}

template<typename T>
void Vector3D<T>::setX(float x) {
    this->x = x;
}

template<typename T>
void Vector3D<T>::setY(float y) {
    this->y = y;
}

#endif //INC_3DE_VECTOR3D_H


