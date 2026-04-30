/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"
#include "HitRecord.hpp"
#include "Math.hpp"
#include <cstdlib>

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

HitRecord Plane::intersect(const Ray &ray, double tMin, double tMax) const
{
    Math::Vector3 normal;
    double originAxis;
    double directionAxis;
    const double eps = 1e-8; //seems to be the appropiate number at least for me, not too much and not to little

    if (_axis == "X") {
        originAxis = ray.origin.x;
        directionAxis = ray.direction.x;
        normal = Math::Vector3(1, 0, 0);
    } else if (_axis == "Y") {
        originAxis = ray.origin.y;
        directionAxis = ray.direction.y;
        normal = Math::Vector3(0, 1, 0);
    } else {
        originAxis = ray.origin.z;
        directionAxis = ray.direction.z;
        normal = Math::Vector3(0, 0, 1);
    }
    if (std::abs(directionAxis) < eps)
        return HitRecord();

    double t = (_pos - originAxis) / directionAxis;

    if (t < tMin || t > tMax)
        return HitRecord();

    Math::Point3 hitPoint = ray.at(t);

    return HitRecord(hitPoint, normal, t, true);
}

}
