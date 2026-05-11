/*
** EPITECH PROJECT, 2026
** DirectionalLight
** File description:
** DirectionalLight
*/
#pragma once

#include <algorithm>
#include "ILight.hpp"

namespace RayTracer {

// directional (infinite distant) light, direction points from the light toward the scene TODO
// contribution at a surface point = Lambert diffuse: max(0, dot(normal, -direction)) * intensity
class DirectionalLight : public ILight {
private:
    Math::Vector3 _direction; // normalized, pointing toward scene (from light source)
    double _intensity;

public:
    DirectionalLight(const Math::Vector3 &direction, double intensity)
        : _direction(direction.normalized()), _intensity(intensity)
    {
    }
    ~DirectionalLight() = default;

    Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal,
        const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override
    {
        const Math::Vector3 toLight = _direction * -1.0;
        const double diffuse = std::max(0.0, normal.dot(toLight)) * _intensity;
        if (diffuse <= 0.0)
            return Math::Vector3(0.0, 0.0, 0.0);

        // shadow ray: offset along normal to avoid self intersecitojn
        const Math::Point3 shadowOrigin(
            point.x + normal.x * 1e-4,
            point.y + normal.y * 1e-4,
            point.z + normal.z * 1e-4
        );
        const Ray shadowRay(shadowOrigin, toLight);
        for (const auto &prim : primitives) {
            if (prim->intersect(shadowRay, 1e-4, 1e9).hit)
                return Math::Vector3(0.0, 0.0, 0.0);
        }
        return Math::Vector3(diffuse, diffuse, diffuse);
    }

    const Math::Vector3 &direction() const { return _direction; }
    double intensity() const { return _intensity; }
};

}
