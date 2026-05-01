/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** Cylinder
*/


#include "Cylinder.hpp"
#include "HitRecord.hpp"

namespace RayTracer {
// A cylinder is a circle extended along the Y axis.
//
// It has 3 parts:
//      - 1 Body
//      - 2 Flat circular caps
//
// BODY:
//  Substitute ray into x² + z² = R²
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

HitRecord Cylinder::intersect(const Ray &ray, double tMin, double tMax) const
{

}
}
