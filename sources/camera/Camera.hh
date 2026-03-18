#pragma once

#include <cmath>

#include "Vector3.hh"

class Camera {
public:
    Vector3 C;
    Vector3 P;
    Vector3 up;
    float fovX;
    float fovY;
    float zmin;

    Camera(
        const Vector3& center,
        const Vector3& lookAt,
        const Vector3& up,
        float fovX,
        float fovY,
        float zmin
    )
        : C(center), P(lookAt), up(up), fovX(fovX), fovY(fovY), zmin(zmin) {}

    Vector3 forward() const {
        return (P - C).normalized();
    }

    Vector3 right() const {
        return forward().cross(up).normalized();
    }

    Vector3 trueUp() const {
        return right().cross(forward()).normalized();
    }

    Vector3 pixelCenter(int px, int py, int width, int height) const {
        const float halfW = zmin * std::tan(fovX * 0.5f);
        const float halfH = zmin * std::tan(fovY * 0.5f);

        const float u = ((static_cast<float>(px) + 0.5f) / static_cast<float>(width)) * 2.0f - 1.0f;
        const float v = 1.0f - ((static_cast<float>(py) + 0.5f) / static_cast<float>(height)) * 2.0f;

        const Vector3 imageCenter = C + forward() * zmin;
        return imageCenter + right() * (u * halfW) + trueUp() * (v * halfH);
    }
};