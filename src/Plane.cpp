/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Plane
*/

#include "Plane.hpp"
#include "HitRecord.hpp"
#include "Math.hpp"
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

//HitRecord Plane::intersect(const Ray &ray, double tMin, double tMax) const
//{
//    Math::Vector3 normal;
//    double originAxis;
//    double directionAxis;
//    double t = (_pos - originAxis) / directionAxis;
//    Math::Point3 hitPoint = ray.at(t);
//
//    //TODO
//    return HitRecord(hitPoint, normal, t, true);
//}

}
