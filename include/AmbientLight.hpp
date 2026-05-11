/*
** EPITECH PROJECT, 2026
** AmbientLight
** File description:
** AmbientLight
*/
#pragma once

#include "ILight.hpp"

namespace RayTracer {

class AmbientLight : public ILight {
private:
    double _intensity;

public:
    explicit AmbientLight(double intensity) : _intensity(intensity) {}
    ~AmbientLight() = default;

    Math::Vector3 contribute(const Math::Point3 &point, const Math::Vector3 &normal,
        const std::vector<std::shared_ptr<IPrimitive>> &primitives) const override
    {
        (void)point;
        (void)normal;
        (void)primitives;
        return Math::Vector3(_intensity, _intensity, _intensity);
    }

    double intensity() const { return _intensity; }
};

}
