#pragma once;

#include "vector3.hh";

class TextureMaterial
{
    public:
    virtual void getColor(const Vector3& p ) = 0;
};


