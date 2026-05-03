/*
** EPITECH PROJECT, 2026
** Cone
** File description:
** Cone
*/

#include "Cone.hpp"
#include "HitRecord.hpp"
#include "Math.hpp"
#include <cmath>

namespace RayTracer {
// A cone is similar to a cylinder, except it narrows to a point at the top.
// That point is called Apex.
//
// It has 2 parts:
//      - 1 Body
//      - 1 Base cap
//
// BODY:
//  The cone equation is: x² + z² = (r/h)² * (y - apex)²
//  Where apex = center.y + height (the tip of the cone)
//  And (r/h) is the slope, how fast the cone widens going down.
//
//  Substitute ray into cone equation -> we get the typical ax² + bx + c = 0
//  Things to take into account:
//      dx = ray.origin.x - center.x
//      dy = ray.origin.y - apex
//      dz = ray.origin.z - center.z
//      slope = r/h
//      k = slope²
//  a = Dx² + Dz² - k * Dy²
//  b = 2*(dx*Dx + dz*Dz - k*dy*Dy)
//  c = dx² + dz² - k*dy²
//  After finding t, check Y is within [center.y, apex] (base to tip)
//
// BASE CAP:
//  The base cap is a plane at y = center.y
//  After finding t, check X and Z are within the circle radius.
//
// We keep the nearest valid hit across the body and base cap.

bool Cone::is_height(const Math::Point3 &point) const
{
    double apex = _center.y + _height;

    return point.y >= _center.y && point.y <= apex;
}

HitRecord Cone::intersect_body(const Ray &ray, double tMin, double tMax) const
{
    double slope = _radius / _height;
    double apex = _center.y + _height;
    double ox = ray.origin.x - _center.x;
    double oy = ray.origin.y - apex;
    double oz = ray.origin.z - _center.z;
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z - (slope * slope) * ray.direction.y * ray.direction.y;
    double b = 2 * (ox * ray.direction.x + oz * ray.direction.z - (slope * slope) * oy * ray.direction.y);
    double c = ox * ox + oz * oz - (slope * slope) * oy * oy;
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return HitRecord();

    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);
    double t;

    if (t1 >= tMin && t1 <= tMax && is_height(ray.at(t1)))
        t = t1;
    else if (t2 >= tMin && t2 <= tMax && is_height(ray.at(t2)))
        t = t2;
    else
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);
    Math::Vector3 normal =
        {
            hit_point.x - _center.x,
            -slope * std::sqrt((hit_point.x - _center.x) * (hit_point.x - _center.x) + (hit_point.z - _center.z) * (hit_point.z - _center.z)),
            hit_point.z - _center.z
        };
    normal = normal.normalized();
    return HitRecord(hit_point, normal, t, true, _color);
}

HitRecord Cone::intersect(const Ray &ray, double tMin, double tMax) const
{
    HitRecord body_hit = intersect_body(ray, tMin, tMax);
    //TODO
    return HitRecord();
}
}
