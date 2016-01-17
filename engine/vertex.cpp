// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#include "vertex.h"

Vertex::Vertex()
: Vertex(0,0) {

}

Vertex::Vertex(float x, float y)
: x{x}, y{y} {

}

float Vertex::getX() const {
    return x;
}

float Vertex::getY() const {
    return y;
}


bool Vertex::operator==(Vertex const &v) const {
    return x == v.x && y == v.y;
}
