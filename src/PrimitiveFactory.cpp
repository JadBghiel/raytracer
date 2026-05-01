/*
** EPITECH PROJECT, 2026
** PrimitiveFactory
** File description:
** PrimitiveFactory
*/

#include "PrimitiveFactory.hpp"
#include "Sphere.hpp"
#include "Plane.hpp"

namespace RayTracer {

std::shared_ptr<IPrimitive> PrimitiveFactory::makeSphere(
    const Math::Point3 &center,
    double radius,
    const Color &color)
{
    return std::make_shared<Sphere>(center, radius, color);
}

std::shared_ptr<IPrimitive> PrimitiveFactory::makePlane(
    const std::string &axis,
    double position,
    const Color &color)
{
    return std::make_shared<Plane>(axis, position, color);
}

}
