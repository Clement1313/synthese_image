#pragma once

#include "Light.hh"
#include "Vector3.hh"

class PointLight : Light
{
public: 
    Vector3 position;
    PointLight (Vector3 p): position(p) {};
    
    Vector3 getPosition() override {
        return position;
    }
};
