#pragma once

#include <cmath>
#include <iostream>

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(float l) const {
        return Vector3(x * l, y * l, z * l);
    }

    Vector3 operator/(float l) const {
        return Vector3(x / l, y / l, z / l);
    }

    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    float length() const {
        return std::sqrt(dot(*this));
    }

    Vector3 normalized() const {
        const float len = length();
        if (len <= 0.0f) {
            return Vector3();
        }
        return *this / len;
    }
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& vect) {
    out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
    return out;
}


