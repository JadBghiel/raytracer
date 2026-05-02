/*
** EPITECH PROJECT, 2026
** Cone
** File description:
** Cone
*/

#ifndef INCLUDED_CONE_HPP
    #define INCLUDED_CONE_HPP

#include "Color.hpp"
#include "IPrimitive.hpp"
#include "Math.hpp"

namespace RayTracer {
class Cone : public IPrimitive
{
    private:
        Math::Point3 _center;
        double _radius;
        double _height;
        Color _color;
    public:
        Cone(Math::Point3 &center, double radius, double height, Color &color) : _center(center), _radius(radius), _height(height), _color(color) {};
        ~Cone() = default;
        HitRecord intersect(const Ray &ray, double tMin, double tMax) const override;
};
}

#endif
