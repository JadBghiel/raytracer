/*
** EPITECH PROJECT, 2026
** LightsParser
** File description:
** LightsParser
*/

#include "parser/LightsParser.hpp"
#include "parser/JsonHelper.hpp"
#include "lights/DirectionalArrayParser.hpp"

namespace RayTracer {
namespace Parser {

bool LightsParser::tryParseLights(const std::string &content, ParsedScene &scene, SceneParseError &error)
{
    const std::size_t lightsPos = content.find("\"lights\"");

    if (lightsPos == std::string::npos)
        return true;

    std::size_t colonPos = content.find(':', lightsPos);

    if (colonPos == std::string::npos || colonPos >= content.size()) {
        error.message = "malformed lights field";
        error.key = "lights";
        return false;
    }

    std::string lightsObj;
    std::size_t objStart = colonPos + 1;

    if (!JsonHelper::tryExtractJsonObject(content, objStart, lightsObj, error)) {
        error.key = "lights";
        return false;
    }

    std::size_t ambientPos = lightsObj.find("\"ambient\"");
    if (ambientPos == std::string::npos) {
        error.message = "lights ambient is required";
        error.key = "lights.ambient";
        return false;
    }

    std::size_t ambientIndex = lightsObj.find(':', ambientPos);
    if (ambientIndex == std::string::npos) {
        error.message = "malformed ambient field";
        error.key = "lights.ambient";
        return false;
    }

    ++ambientIndex;
    if (!JsonHelper::tryExtractJsonNumber(lightsObj, ambientIndex, scene.ambientLight, error)) {
        error.key = "lights.ambient";
        return false;
    }
    if (scene.ambientLight < 0.0 || scene.ambientLight > 1.0) {
        error.message = "ambient must be between 0.0 and 1.0";
        error.key = "lights.ambient";
        return false;
    }

    double defaultDirectionalIntensity = 1.0;
    std::size_t diffusePos = lightsObj.find("\"diffuse\"");
    if (diffusePos != std::string::npos) {
        std::size_t diffuseIndex = lightsObj.find(':', diffusePos);
        if (diffuseIndex == std::string::npos) {
            error.message = "malformed diffuse field";
            error.key = "lights.diffuse";
            return false;
        }
        ++diffuseIndex;
        if (!JsonHelper::tryExtractJsonNumber(lightsObj, diffuseIndex, defaultDirectionalIntensity, error)) {
            error.key = "lights.diffuse";
            return false;
        }
        if (defaultDirectionalIntensity < 0.0 || defaultDirectionalIntensity > 1.0) {
            error.message = "diffuse must be between 0.0 and 1.0";
            error.key = "lights.diffuse";
            return false;
        }
    }

    return Lights::parseDirectionalArray(lightsObj, defaultDirectionalIntensity,
        scene.directionalLights, error);
}

}
}
