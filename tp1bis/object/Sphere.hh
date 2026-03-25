#include "Object.hh"
#include "../vector3/Vector3.hh"

class Sphere: public Object
{
public:
    Vector3 center;
    float radius;

    Sphere (Vector3 center, float radius, TextureMaterial* material): Object(material), center(center), radius(radius) {};
    bool intersect(const Ray& ray, float& dist) const override;
    Vector3 normal(const Vector3& surfacePoint) const override;
    MaterialInfo getMaterial(const Vector3& point) const override; 
};