/*
** EPITECH PROJECT, 2026
** Renderer
** File description:
** Renderer
*/
#pragma once

#include <string>
#include "Scene.hpp"

namespace RayTracer {

class Renderer {
public:
    // render scene to a ppm file at path
    static void render(const Scene &scene, const std::string &outputPath);

private:
    // build the ray for pixel (px, py
    static Ray cameraRay(const Camera &camera, int px, int py);

    // shade the nearest hit using all lights in the scene
    static Color shade(const HitRecord &hit, const Scene &scene);
};

}
