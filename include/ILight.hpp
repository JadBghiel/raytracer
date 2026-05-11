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
#include "IPrimitive.hpp"

namespace RayTracer {

class ILight {
public:
    virtual ~ILight() = default;
// compute light contribution at the given point with the given normal
    // returns a vector representing the light intensity/color contribution
    virtual Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal,
        const std::vector<std::shared_ptr<IPrimitive>> &primitives) const = 0;
};

}
