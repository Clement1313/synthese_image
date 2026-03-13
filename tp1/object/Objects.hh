#pragma once

#include "TextureMaterial.hh"

class Objects
{
public: 
    TextureMaterial* material;

    Objects(TextureMaterial* t);

    virtual bool intersect()

};
