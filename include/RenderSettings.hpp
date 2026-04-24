/*
** EPITECH PROJECT, 2026
** RenderSettings
** File description:
** RenderSettings
*/
#pragma once

namespace RayTracer {

class RenderSettings {
public:
    int samplesPerPixel = 1;
    int maxBounces = 10;
    double epsilon = 1e-6;

    RenderSettings() = default;
    RenderSettings(int spp, int bounces, double eps)
        : samplesPerPixel(spp), maxBounces(bounces), epsilon(eps)
    {
    }
};

}
