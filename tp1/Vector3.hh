#pragma once;

using namespace std;

#include <cmath>
#include <iostream>


class Vector3 {
public:
    float x,y,z;

    Vector3(): x(0), y(0), z(0) {};
    Vector3(float x, float y, float z): x(x), y(y), z(z) {};

    Vector3 Vector3::operator+(const Vector3& v) const {
        return Vector3(x+v.x, y+v.y, z+v.z);
    }

    Vector3 Vector3::operator+(const float& v) const {
        return Vector3(x+v, y+v, z+v);
    }

    Vector3 Vector3::operator-(const Vector3& v) const {
        return Vector3(x-v.x, y-v.y, z-v.z);
    }

    Vector3 Vector3::operator-(const float& v) const {
        return Vector3(x-v, y-v, z-v);
    }

    Vector3 Vector3::operator*(const float& l) const {
        return Vector3(x*l, y*l, z*l);
    }

    float dot(const Vector3& v) const {
        return x*v.x + y*v.y + z*v.z;
    }

    float length() const {
        return sqrt(dot(*this));
    }
};


ostream& operator<<(ostream &out, Vector3 vect) {
    out << "(" << vect.x << ", " << vect.y << "," << vect.z << ")";
    return out;
}


