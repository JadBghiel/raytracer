/*
** EPITECH PROJECT, 2026
** ILight
** File description:
** ILight
*/
#pragma once

#include <memory>
#include <vector>
#include "Math.hpp"
#include <memory>
#include <vector>

namespace RayTracer {

class IPrimitive;

class ILight {
public:
    virtual ~ILight() = default;
// compute light contribution at the given point with the given normal
    // returns a vector representing the light intensity/color contribution
    // primitives are passed here so lights can cast shadow rays
    // and check if any object blocks the path to the light source
    virtual Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal, const std::vector<std::shared_ptr<IPrimitive>> &primitives) const = 0;
};

}
