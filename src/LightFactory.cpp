/*
** EPITECH PROJECT, 2026
** LightFactory
** File description:
** LightFactory
*/

#include "LightFactory.hpp"
#include "AmbientLight.hpp"
#include "DirectionalLight.hpp"

namespace RayTracer {

std::shared_ptr<ILight> LightFactory::makeAmbientLight(double intensity)
{
    return std::make_shared<AmbientLight>(intensity);
}

std::shared_ptr<ILight> LightFactory::makeDirectionalLight(
    const Math::Vector3 &direction,
    double intensity)
{
    return std::make_shared<DirectionalLight>(direction, intensity);
}

}
