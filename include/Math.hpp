/*
** EPITECH PROJECT, 2026
** Math
** File description:
** Math
*/
#pragma once

#include <cmath>

namespace Math {

class Vector3 {
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vector3() = default;
    Vector3(double xValue, double yValue, double zValue)
        : x(xValue), y(yValue), z(zValue)
    {
    }

    // ||v|| = sqrt(x^2 + y^2 + z^2)
    double length() const
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    // v · w = vx * wx + vy * wy + vz * wz
    double dot(const Vector3 &other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z);
    }

    // v / ||v||, with zero vector protection
    Vector3 normalized() const
    {
        const double value = length();

        if (value == 0.0)
            return Vector3();
        return Vector3(x / value, y / value, z / value);
    }

    Vector3 &normalize()
    {
        const double value = length();

        if (value == 0.0)
            return *this;
        x /= value;
        y /= value;
        z /= value;
        return *this;
    }

    Vector3 &operator+=(const Vector3 &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3 &operator-=(const Vector3 &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3 &operator*=(const Vector3 &other)
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3 &operator/=(const Vector3 &other)
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3 &operator*=(double scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3 &operator/=(double scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3 operator+(const Vector3 &other) const
    {
        return Vector3(*this) += other;
    }

    Vector3 operator-(const Vector3 &other) const
    {
        return Vector3(*this) -= other;
    }

    Vector3 operator*(const Vector3 &other) const
    {
        return Vector3(*this) *= other;
    }

    Vector3 operator/(const Vector3 &other) const
    {
        return Vector3(*this) /= other;
    }

    Vector3 operator*(double scalar) const
    {
        return Vector3(*this) *= scalar;
    }

    Vector3 operator/(double scalar) const
    {
        return Vector3(*this) /= scalar;
    }
};

inline Vector3 operator*(double scalar, const Vector3 &vector)
{
    return vector * scalar;
}

class Point3 {
public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Point3() = default;
    Point3(double xValue, double yValue, double zValue)
        : x(xValue), y(yValue), z(zValue)
    {
    }

    // P + v = (px + vx, py + vy, pz + vz)
    Point3 &operator+=(const Vector3 &vector)
    {
        x += vector.x;
        y += vector.y;
        z += vector.z;
        return *this;
    }

    // translate a point by a vector
    Point3 operator+(const Vector3 &vector) const
    {
        return Point3(*this) += vector;
    }
};

using Vector3D = Vector3;
using Point3D = Point3;

} // namespace Math