#pragma once;

#include "Vector3.hh";
#include "Color.hh";

class TextureMaterial
{
public:
    Color color;
    float kd;
    float ks;
    float ns;

    virtual Color getColor(const Vector3& p ) = 0;
};


