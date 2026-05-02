/*
** EPITECH PROJECT, 2026
** Plane
** File description:
** Plane
*/

#ifndef INCLUDED_PLANE_HPP
    #define INCLUDED_PLANE_HPP

#include "Color.hpp"
#include "IPrimitive.hpp"
#include <string>

namespace RayTracer {
class Plane : public IPrimitive
{
    private:
        std::string _axis;
        double _pos;
        Color _color;
    public:
        Plane(const std::string &axis, double pos, const Color &color) : _axis(axis), _pos(pos), _color(color) {};
        ~Plane() = default;
        HitRecord intersect(const Ray &ray, double tMin, double tMax) const override;
};
}

#endif
