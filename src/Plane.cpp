/*
** EPITECH PROJECT, 2026
** Plane
** File description:
** Plane
*/

#include "../include/Plane.hpp"
#include "../include/HitRecord.hpp"
#include "../include/Math.hpp"
#include <cmath>

namespace RayTracer {
// A plane is a flat and infinite surface defined by:
//      - Axis: (x, y or z) which is its normal direction
//      - A position along that axis
//
// EXAMPLE: axis=y, position=-1 -> horizontal floor at y=-1
//
// To find where the ray hits the plane:
//      t = (position - ray origin axis) / ray direction axis
//
// Special case:
//      - If ray.direction.axis is 0, the ray is parallel to the plane so it won't hit
//
// The normal is simply the axis direction:
//      - axis=x -> normal(1, 0, 0)
//      - axis=y -> normal(0, 1, 0)
//      - axis=z -> normal(0, 0, 1)
//
// We will also need the use of a number extremely close to 0, but not quite.
// That number is called epsilon
// we need it because computers can't represent decimal numbers perfectly.
// This specific number will save us when rays are parallel to the Plane.
//
// website: https://stackoverflow.com/questions/13436125/how-big-should-epsilon-be-when-checking-if-dot-product-is-close-to-0
//
// It is important to note that having the number from the website will make the Raytracer less efficient
// 10*DBL_MIN = 2.2e-308, that number is TOO small for our liking
// It won't protect well because computer imprecission is worse than that.

HitRecord Plane::intersect(const Ray &ray, double tMin, double tMax) const
{
    Math::Vector3 normal;
    double origin_axis;
    double direction_axis;
    const double eps = 1e-8; //seems to be the appropiate number at least for me, not too much and not to little

    if (_axis == "X") {
        origin_axis = ray.origin.x;
        direction_axis = ray.direction.x;
        normal = Math::Vector3(1, 0, 0);
    } else if (_axis == "Y") {
        origin_axis = ray.origin.y;
        direction_axis = ray.direction.y;
        normal = Math::Vector3(0, 1, 0);
    } else {
        origin_axis = ray.origin.z;
        direction_axis = ray.direction.z;
        normal = Math::Vector3(0, 0, 1);
    }
    if (std::abs(direction_axis) < eps)
        return HitRecord();

    double t = (_pos - origin_axis) / direction_axis;

    if (t < tMin || t > tMax)
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);

    // checkerboard: pick two axes perpendicular to the plane normal
    int ia, ib;
    if (_axis == "Y") {
        ia = static_cast<int>(std::floor(hit_point.x));
        ib = static_cast<int>(std::floor(hit_point.z));
    } else if (_axis == "X") {
        ia = static_cast<int>(std::floor(hit_point.y));
        ib = static_cast<int>(std::floor(hit_point.z));
    } else {
        ia = static_cast<int>(std::floor(hit_point.x));
        ib = static_cast<int>(std::floor(hit_point.y));
    }
    const bool dark = (ia + ib) % 2 != 0;
    const Color tileColor = dark
        ? Color(_color.r * 0.15, _color.g * 0.15, _color.b * 0.15)
        : _color;

    return HitRecord(hit_point, normal, t, true, tileColor);
}
}
