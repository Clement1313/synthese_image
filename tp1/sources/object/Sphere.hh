#pragma once

#include <cmath>

#include "Objects.hh"

class Sphere : public Object {
public:
    Vector3 center;
    float radius;

    Sphere(const Vector3& c, float r, const TextureMaterial* material)
        : Object(material), center(c), radius(r) {}

    bool intersect(const Ray& ray, float& t) const override {
        const Vector3 oc = ray.origin - center;
        const float a = ray.direction.dot(ray.direction);
        const float b = 2.0f * oc.dot(ray.direction);
        const float c = oc.dot(oc) - radius * radius;

        const float disc = b * b - 4.0f * a * c;
        if (disc < 0.0f) {
            return false;
        }

        const float sqrtDisc = std::sqrt(disc);
        const float t0 = (-b - sqrtDisc) / (2.0f * a);
        const float t1 = (-b + sqrtDisc) / (2.0f * a);

        const float eps = 1e-5f;
        if (t0 > eps) {
            t = t0;
            return true;
        }
        if (t1 > eps) {
            t = t1;
            return true;
        }

        return false;
    }

    Vector3 normalAt(const Vector3& p) const override {
        return (p - center).normalized();
    }
};
