/*
** EPITECH PROJECT, 2026
** Cone
** File description:
** Cone
*/

#include "Cone.hpp"

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
HitRecord Cone::intersect(const Ray &ray, double tMin, double tMax) const
{
    //TODO
    return HitRecord(); //not finished
}
}
