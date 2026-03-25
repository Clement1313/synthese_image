#pragma once

#include "../vector3/Vector3.hh"

class Light
{
public:
    virtual Vector3 getPosition() const = 0;
};