#pragma once

#include "TextureMaterial.hh"

class UniformTexture : public TextureMaterial {
public:
    MaterialSample params;

    explicit UniformTexture(const MaterialSample& p) : params(p) {}

    MaterialSample sample(const Vector3&) const override {
        return params;
    }
};