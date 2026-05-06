/*
** EPITECH PROJECT, 2026
** PrimitiveFactory
** File description:
** PrimitiveFactory
*/

#include "../include/PrimitiveFactory.hpp"
#include "../include/Color.hpp"
#include "../include/IPrimitive.hpp"
#include "../include/Math.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plane.hpp"
#include "../include/Cylinder.hpp"
#include "../include/Cone.hpp"
#include <memory>

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

std::shared_ptr<IPrimitive> PrimitiveFactory::makeCylinder(
    const Math::Point3 &center,
    double radius,
    double height,
    const Color &color)
{
    return std::make_shared<Cylinder>(center, radius, height, color);
}

std::shared_ptr<IPrimitive> PrimitiveFactory::makeCone(
    const Math::Point3 &center,
    double radius,
    double height,
    const Color &color)
{
    return std::make_shared<Cone>(center, radius, height, color);
}

}
