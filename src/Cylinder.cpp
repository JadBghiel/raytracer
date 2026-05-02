/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/


#include "Cylinder.hpp"
#include "HitRecord.hpp"
#include "Math.hpp"
#include <cmath>
#include <cstdlib>

namespace RayTracer {
// A cylinder is a circle extended along the Y axis.
//
// It has 3 parts:
//      - 1 Body
//      - 2 Flat circular caps
//
// BODY:
//  Substitute ray into x² + z² = R² -> we will get the typical ax² + bx + c = 0
//  The final thing would be (Dx² + Dz²)*t² + (2*Ox*Dx + 2*Oz*Dz)*t + (Ox² + Oz² - R²) = 0
//  a = Dx² + Dz²
//  b = 2*((Ox-Cx)*Dx + (Oz-Cz)*Dz)
//  c = (Ox-Cx)² + (Oz-Cz)² - R²
//  After finding t, check Y is within [center.y - h/2, center.y + h/2]
//
// CAPS:
//  Each cap is a plane at y = center.y +- height/2
//  After finding t, check X and Z are within the circle radius
//
// We keep the nearest valid hit across the body and both caps, just like in any other shape.

bool Cylinder::is_height(const Math::Point3 &point) const
{
    double half_cylinder = _height / 2;

    return point.y >= (_center.y - half_cylinder) && point.y <= (_center.y + half_cylinder);
}

bool Cylinder::is_cap(const Math::Point3 &point) const
{
    double dx = point.x - _center.x;
    double dz = point.z - _center.z;

    return (dx * dx + dz * dz) <= (_radius * _radius);
}

HitRecord Cylinder::intersect_body(const Ray &ray, double tMin, double tMax) const
{
    double ox = ray.origin.x - _center.x;
    double oz = ray.origin.z - _center.z;
    double a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
    double b = 2 * (ox * ray.direction.x + oz * ray.direction.z);
    double c = ox * ox + oz * oz - (_radius * _radius);
    double discriminant = (b * b) - (4 * a * c);

    if (discriminant < 0)
        return HitRecord();

    double sqrt_discriminant = std::sqrt(discriminant);
    double t = (-b - sqrt_discriminant) / (2 * a);

    if (t < tMin || t > tMax) {
        t = (-b + sqrt_discriminant) / (2 * a);
        if (t < tMin || t > tMax)
            return HitRecord();
    }
    Math::Point3 hit_point = ray.at(t);
    Math::Vector3 normal =
        {
            (hit_point.x - _center.x) / _radius,
            0,
            (hit_point.z - _center.z) / _radius
        };
    return HitRecord(hit_point, normal, t, true);
}

HitRecord Cylinder::intersect_cap(const Ray &ray, double tMin, double tMax, double cap_y) const
{
    const double eps = 1e-8;
    double t = (cap_y - ray.origin.y) / ray.direction.y;

    if (std::abs(ray.direction.y) < eps)
        return HitRecord();
    if (t < tMin || t > tMax)
        return HitRecord();
    Math::Point3 hit_point = ray.at(t);
    if (!is_cap(hit_point))
        return HitRecord();
    Math::Vector3 normal;
    if (cap_y > _center.y)
        normal = {0, 1, 0};
    else
        normal = {0, -1, 0};
    return HitRecord(hit_point, normal, t, true);
}

HitRecord Cylinder::intersect(const Ray &ray, double tMin, double tMax) const
{
    double middle = _height/2; //useful for caps
    HitRecord body_hit = intersect_body(ray, tMin, tMax);
    HitRecord top_hit = intersect_cap(ray, tMin, tMax, _center.y + middle);
    HitRecord bottom_hit = intersect_cap(ray, tMin, tMax, _center.y - middle);
    //TODO
}
}
