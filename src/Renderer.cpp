/*
** EPITECH PROJECT, 2026
** Renderer
** File description:
** Renderer
*/

#include "Renderer.hpp"
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

