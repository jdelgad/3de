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

#endif //INC_3DE_VECTOR3D_H
