#pragma once

#include "Light.hh"
#include "../vector3/Vector3.hh"
class PointLight: public Light
{
public:
    Vector3 position;

    PointLight(Vector3 position): position(position) {};

    Vector3 getPosition() const override {
        return position;
    }
};