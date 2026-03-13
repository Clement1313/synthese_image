#pragma once;

#include "TextureMaterial.hh";
#include "Color.hh";

class UniformTexture: TextureMaterial
{
public:
    Color color;

    UniformTexture(Color c): color(c) {}
    
};