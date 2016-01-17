// MIT License, (C)2016
// Created by jdelgad on 1/16/16.
//

#ifndef INC_3DE_VERTEX_H
#define INC_3DE_VERTEX_H


class Vertex {
public:
    Vertex();
    Vertex(float x, float y);

    float getX() const;
    float getY() const;

private:
    float x;
    float y;
};


#endif //INC_3DE_VERTEX_H
