#pragma once

#include "../material/TextureMaterial.hh"
#include "../Vector3.hh"

struct Ray {
    Vector3 origin;
    Vector3 direction;

    Ray(const Vector3& origin, const Vector3& direction)
        : origin(origin), direction(direction) {}
};

class Object
{
public: 
    const TextureMaterial* material;

    explicit Object(const TextureMaterial* t) : material(t) {}
    virtual ~Object() = default;

    virtual bool intersect(const Ray& ray, float& t) const = 0;
    virtual Vector3 normalAt(const Vector3& p) const = 0;
};
