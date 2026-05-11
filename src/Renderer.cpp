/*
** EPITECH PROJECT, 2026
** Renderer
** File description:
** Renderer
*/

#include "../include/Renderer.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <limits>

namespace RayTracer {

// camera ray generation
//
// build an orthonormal camera basis from the stored direction, then map each
// pixel centre to a dir vector on the perspective image plane
//
// coords convention FOR NOW NOT FINALM (right handed):
//   forward = camera.direction (into the scene)
//   right = cross(forward, worldUp) normalised
//   up = cross(right, forward) normalised
//
// normalized device coords (ndc): https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/standard-coordinate-systems.html
// https://computergraphics.stackexchange.com/questions/7980/problem-of-understanding-the-coordinate-systems-involved-in-ray-tracing
// ndc range: x ecist in [-1, 1] left->right, y exists in  [1, -1] top->bottom
// halfWidth = tan(hFOV / 2), halfHeight = halfWidth / aspectRatio

Ray Renderer::cameraRay(const Camera &camera, int px, int py)
{
    const double aspectRatio =
        static_cast<double>(camera.resolutionWidth) / camera.resolutionHeight;
    const double halfWidth =
        std::tan(Math::Vector3::degrees_to_radians(camera.fieldOfView / 2.0));
    const double halfHeight = halfWidth / aspectRatio;

    Math::Vector3 forward = camera.direction; // already normalised by parser
    Math::Vector3 worldUp(0.0, 1.0, 0.0);
    Math::Vector3 right = forward.cross(worldUp).normalized();

    // fallback when forward is parallel to worldUp (straight up/down look)
    if (right.length() < 1e-6) {
        worldUp = Math::Vector3(0.0, 0.0, 1.0);
        right = forward.cross(worldUp).normalized();
    }
    const Math::Vector3 up = right.cross(forward).normalized();

    const double ndcX =
        (2.0 * (px + 0.5) / camera.resolutionWidth) - 1.0;
    const double ndcY =
        1.0 - (2.0 * (py + 0.5) / camera.resolutionHeight);

    const Math::Vector3 dir =
        (forward + right * (ndcX * halfWidth) + up * (ndcY * halfHeight))
        .normalized();

    return Ray(camera.position, dir);
}

// flat shading (ambient + directional Lambert)
//
// totalLight = sum of all ILight::contribute() calls
// finalColor = hitColor * clamp(totalLight, 0, 1)  (component-wise)

Color Renderer::shade(const HitRecord &hit, const Scene &scene)
{
    Math::Vector3 totalLight(0.0, 0.0, 0.0);
    for (const auto &light : scene.lights)
        totalLight += light->contribute(hit.point, hit.normal, scene.primitives);

    const double lr = std::min(1.0, std::max(0.0, totalLight.x));
    const double lg = std::min(1.0, std::max(0.0, totalLight.y));
    const double lb = std::min(1.0, std::max(0.0, totalLight.z));

    return Color(hit.color.r * lr, hit.color.g * lg, hit.color.b * lb);
}

// ppm writer + pixel loop
//
// for each pixel:
//   1. cast ray from camera through pixel center
//   2. intersect all primitives, keep nearest hit (smallest positive t)
//   3. shade or use background colour
// write p3 ppm to outputPath

void Renderer::render(const Scene &scene, const std::string &outputPath)
{
    const int width  = scene.camera.resolutionWidth;
    const int height = scene.camera.resolutionHeight;

    constexpr double tMin = 1e-6;
    const double     tMax = std::numeric_limits<double>::max();

    // bg: dark blue grey gradient (top darker, bottom lighter)
    const Color background(0.05, 0.07, 0.15);

    std::ofstream out(outputPath);
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int py = 0; py < height; ++py) {
        for (int px = 0; px < width; ++px) {
            const Ray ray = cameraRay(scene.camera, px, py);

            // find nearest hit across all primitives
            HitRecord nearest;
            double nearestT = tMax;

            for (const auto &prim : scene.primitives) {
                const HitRecord hr = prim->intersect(ray, tMin, nearestT);
                if (hr.hit) {
                    nearest  = hr;
                    nearestT = hr.t;
                }
            }

            const Color pixel = nearest.hit ? shade(nearest, scene) : background;

            const int r = static_cast<int>(
                std::min(1.0, std::max(0.0, pixel.r)) * 255);
            const int g = static_cast<int>(
                std::min(1.0, std::max(0.0, pixel.g)) * 255);
            const int b = static_cast<int>(
                std::min(1.0, std::max(0.0, pixel.b)) * 255);

            out << r << " " << g << " " << b << "\n";
        }
    }
}

}
