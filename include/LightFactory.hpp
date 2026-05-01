/*
** EPITECH PROJECT, 2026
** LightFactory
** File description:
** LightFactory
*/
#pragma once

#include <memory>
#include "ILight.hpp"
#include "Math.hpp"

namespace RayTracer {

// centralizes construction of all light types
// maps (type + parameters) -> real ILight instance
class LightFactory {
public:
    static std::shared_ptr<ILight> makeAmbientLight(double intensity);

    static std::shared_ptr<ILight> makeDirectionalLight(
        const Math::Vector3 &direction,
        double intensity);
};

}
