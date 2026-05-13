/*
** EPITECH PROJECT, 2026
** RenderSettings
** File description:
** RenderSettings
*/
#pragma once

#include <thread>
namespace RayTracer {

class RenderSettings {
public:
    int samplesPerPixel = 1;
    int maxBounces = 10;
    double epsilon = 1e-6;
    int threads = std::thread::hardware_concurrency(); //put static_cast<int> just in case it gives compilation warning

    RenderSettings() = default;
    RenderSettings(int spp, int bounces, double eps, int threadCount)
        : samplesPerPixel(spp), maxBounces(bounces), epsilon(eps), threads(threadCount)
    {
    }
};

}
