#pragma once

#include "Color.hh"
#include "Vector3.hh"

struct MaterialSample {
    Color color;
    float kd;
    float ks;
    float ns;

    MaterialSample() : color(), kd(1.0f), ks(0.0f), ns(1.0f) {}
    MaterialSample(const Color& color, float kd, float ks, float ns)
        : color(color), kd(kd), ks(ks), ns(ns) {}
};

class TextureMaterial {
public:
    virtual ~TextureMaterial() = default;
    virtual MaterialSample sample(const Vector3& p) const = 0;
};


