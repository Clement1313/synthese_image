#pragma once

#include "Vector3.hh"

class Light
{
public: 
    virtual ~Light() = default;
    virtual Vector3 getPosition() const = 0;
};
