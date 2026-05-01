/*
** EPITECH PROJECT, 2026
** SceneLoader
** File description:
** SceneLoader
*/

#include "SceneLoader.hpp"
#include "SceneBuilder.hpp"
#include "PrimitiveFactory.hpp"
#include "LightFactory.hpp"

namespace RayTracer {

namespace {

// colors in the scene file are 0 to 255, normalize to 0 to 1 for rendering math
Color normalizeColor(const ParsedColor &pc)
{
    return Color(pc.r / 255.0, pc.g / 255.0, pc.b / 255.0);
}

}

Scene SceneLoader::load(const ParsedScene &parsed)
{
    SceneBuilder builder;

    // camera: already a fully constructed Camera from the parser
    builder.withCamera(parsed.camera);

    // ambient light, one global ambient term
    if (parsed.ambientLight > 0.0)
        builder.addLight(LightFactory::makeAmbientLight(parsed.ambientLight));

    // directional lights
    for (const auto &dl : parsed.directionalLights)
        builder.addLight(LightFactory::makeDirectionalLight(dl.direction, dl.intensity));

    // spheres: apply translation to center at load time
    for (const auto &ps : parsed.spheres) {
        const Math::Point3 center(
            ps.center.x + ps.translation.x,
            ps.center.y + ps.translation.y,
            ps.center.z + ps.translation.z);
        builder.addPrimitive(
            PrimitiveFactory::makeSphere(center, ps.radius, normalizeColor(ps.color)));
    }

    // planes: apply translation along the plane's own axis at load time
    for (const auto &pp : parsed.planes) {
        double position = pp.position;
        if (pp.axis == "X")
            position += pp.translation.x;
        else if (pp.axis == "Y")
            position += pp.translation.y;
        else
            position += pp.translation.z;
        builder.addPrimitive(
            PrimitiveFactory::makePlane(pp.axis, position, normalizeColor(pp.color)));
    }

    return builder.build();
}

}
