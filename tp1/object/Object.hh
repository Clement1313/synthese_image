#pragma once

#include "../texture/TextureMaterial.hh"
#include "../vector3/Vector3.hh"

struct Ray {
    Vector3 direction;
    Vector3 origin;
    Ray (const Vector3& direction, const Vector3& origin): direction(direction), origin(origin) {}
};

class Object
{
public:
    TextureMaterial* material;

    Object(TextureMaterial* material): material(material) {}
    
    virtual bool intersect(const Ray& ray, float& dist) const = 0;
    virtual Vector3 normal(const Vector3& surfacePoint) const = 0;
    virtual MaterialInfo getMaterial(const Vector3& point) const = 0; 
};