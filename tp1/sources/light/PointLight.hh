#pragma once

#include "Light.hh"
#include "Vector3.hh"

class PointLight : public Light
{
public: 
    Vector3 position;
    explicit PointLight(Vector3 p) : position(p) {}
    
    Vector3 getPosition() const override {
        return position;
    }
};
