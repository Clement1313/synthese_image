#include "Sphere.hh"
#include "../vector3/Vector3.hh"

#include <algorithm>
#include <cmath>

bool Sphere::intersect(const Ray& ray, float& dist) const {
    Vector3 oc = ray.origin - this->center;

    float a = ray.direction.dot(ray.direction);
    float b = 2 * oc.dot(ray.direction);
    float c = oc.dot(oc) - this->radius * this->radius;

    float delta = b*b-4*a*c;

    if (delta < 0) return false;

    if (delta == 0) {
        float d = -b/(2*a);
        if (d < 0) return false;
        
        dist = d;
        return true;
    }

    if (delta > 0) {
        float sqrt_delta = std::sqrt(delta);
        float d1 = (-b+sqrt_delta) / (2*a);
        float d2 = (-b-sqrt_delta) / (2*a);

        if (d1 < 0 && d2 < 0) return false;
        if (d1 < 0 && d2 > 0) {
            dist = d2;
            return true;
        }
        if (d1 > 0 && d2 < 0) {
            dist = d1;
            return true;
        }
        if (d1 > 0 && d2 > 0) {
            dist = std::min(d1, d2);
            return true;
        }
        return false;
    }

    return false;
}

Vector3 Sphere::normal(const Vector3& surfacePoint) const {
    Vector3 t = surfacePoint - this->center;
    Vector3 normalized = t/t.norm();
    return normalized;
}

MaterialInfo Sphere::getMaterial(const Vector3& point) const {
    return material->getMaterial(point);
}
