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

    Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal) const override
    {
        (void)point;
        // toward light vector = -_direction
        const Math::Vector3 toLight = _direction * -1.0;
        const double diffuse = std::max(0.0, normal.dot(toLight)) * _intensity;
        return Math::Vector3(diffuse, diffuse, diffuse);
    }

    const Math::Vector3 &direction() const { return _direction; }
    double intensity() const { return _intensity; }
};

}
