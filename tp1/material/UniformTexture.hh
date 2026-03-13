#pragma once;

#include "TextureMaterial.hh";
#include "Color.hh";

class UniformTexture: TextureMaterial
{
public:
    Color color;
    float kd;
    float ks;
    float ns;

    UniformTexture(Color c): color(c) {}
    virtual Color getColor(const Vector3& p ) override {
        return color;
    }

};