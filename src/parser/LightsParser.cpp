/*
** EPITECH PROJECT, 2026
** LightsParser
** File description:
** LightsParser
*/

#include "../../include/parser/LightsParser.hpp"
#include "../../include/parser/JsonHelper.hpp"
#include "../../include/SceneParser.hpp"
#include <string>
#include <iostream>


namespace RayTracer {
namespace Parser {

bool LightsParser::tryParseLights(const std::string &content,
                                  ParsedScene &parsed,
                                  SceneParseError &error)
{
    std::size_t lightsPos = content.find("\"lights\"");
    if (lightsPos == std::string::npos) {
        error.message = "lights section is required";
        error.key = "lights";
        return false;
    }

    std::size_t colon = content.find(':', lightsPos);
    if (colon == std::string::npos) {
        error.message = "malformed lights section";
        error.key = "lights";
        return false;
    }
    ++colon;

    std::string lightsObj;
    if (!JsonHelper::tryExtractJsonObject(content, colon, lightsObj, error)) {
        error.key = "lights";
        return false;
    }

    // ambient
    std::size_t ambPos = lightsObj.find("\"ambient\"");
    if (ambPos == std::string::npos) {
        error.message = "ambient light is required";
        error.key = "lights.ambient";
        return false;
    }
    std::size_t ambColon = lightsObj.find(':', ambPos);
    if (ambColon == std::string::npos) {
        error.message = "malformed ambient field";
        error.key = "lights.ambient";
        return false;
    }
    ++ambColon;
    if (!JsonHelper::tryExtractJsonNumber(lightsObj, ambColon, parsed.ambientLight, error)) {
        error.key = "lights.ambient";
        return false;
    }
    if (parsed.ambientLight < 0.0 || parsed.ambientLight > 1.0) {
        error.message = "ambient must be between 0.0 and 1.0";
        error.key = "lights.ambient";
        return false;
    }

    // diffuse default for directional lights
    double defaultDiffuse = 1.0;
    std::size_t diffPos = lightsObj.find("\"diffuse\"");
    if (diffPos != std::string::npos) {
        std::size_t diffColon = lightsObj.find(':', diffPos);
        if (diffColon == std::string::npos) {
            error.message = "malformed diffuse field";
            error.key = "lights.diffuse";
            return false;
        }
        ++diffColon;
        if (!JsonHelper::tryExtractJsonNumber(lightsObj, diffColon, defaultDiffuse, error)) {
            error.key = "lights.diffuse";
            return false;
        }
        if (defaultDiffuse < 0.0 || defaultDiffuse > 1.0) {
            error.message = "diffuse must be between 0.0 and 1.0";
            error.key = "lights.diffuse";
            return false;
        }
    }

    // directional lights
    std::size_t dirPos = lightsObj.find("\"directional\"");
    if (dirPos != std::string::npos) {
        std::size_t dirColon = lightsObj.find(':', dirPos);
        if (dirColon == std::string::npos) {
            error.message = "malformed directional lights field";
            error.key = "lights.directional";
            return false;
        }
        ++dirColon;

        std::string dirArray;
        if (!JsonHelper::tryExtractJsonArray(lightsObj, dirColon, dirArray, error)) {
            error.key = "lights.directional";
            return false;
        }

        std::size_t scan = 0;
        while (true) {
            std::string lightObj;
            if (!JsonHelper::nextObjectInArray(dirArray, scan, lightObj, error))
                break;

            ParsedDirectionalLight dl;

            // direction x,y,z
            std::size_t xPos = lightObj.find("\"x\"");
            std::size_t yPos = lightObj.find("\"y\"");
            std::size_t zPos = lightObj.find("\"z\"");
            if (xPos == std::string::npos || yPos == std::string::npos || zPos == std::string::npos) {
                error.message = "directional light must contain x, y, z";
                error.key = "lights.directional";
                return false;
            }

            std::size_t xColon = lightObj.find(':', xPos) + 1;
            std::size_t yColon = lightObj.find(':', yPos) + 1;
            std::size_t zColon = lightObj.find(':', zPos) + 1;

            if (!JsonHelper::tryExtractJsonNumber(lightObj, xColon, dl.direction.x, error)) return false;
            if (!JsonHelper::tryExtractJsonNumber(lightObj, yColon, dl.direction.y, error)) return false;
            if (!JsonHelper::tryExtractJsonNumber(lightObj, zColon, dl.direction.z, error)) return false;

            if (dl.direction.length() == 0.0) {
                error.message = "directional light direction cannot be zero vector";
                error.key = "lights.directional.direction";
                return false;
            }
            dl.direction.normalize();

            // intensity
            dl.intensity = defaultDiffuse;
            std::size_t iPos = lightObj.find("\"intensity\"");
            if (iPos != std::string::npos) {
                std::size_t iColon = lightObj.find(':', iPos) + 1;
                if (!JsonHelper::tryExtractJsonNumber(lightObj, iColon, dl.intensity, error)) {
                    error.key = "lights.directional.intensity";
                    return false;
                }
                if (dl.intensity < 0.0 || dl.intensity > 1.0) {
                    error.message = "directional light intensity must be between 0.0 and 1.0";
                    error.key = "lights.directional.intensity";
                    return false;
                }
            }

            parsed.directionalLights.push_back(dl);
        }
    }

    // point lights
    std::size_t pointPos = lightsObj.find("\"point\"");
    if (pointPos != std::string::npos) {
        std::size_t pointColon = lightsObj.find(':', pointPos);
        if (pointColon == std::string::npos) {
            error.message = "malformed point lights field";
            error.key = "lights.point";
            return false;
        }
        ++pointColon;

        std::string pointArray;
        if (!JsonHelper::tryExtractJsonArray(lightsObj, pointColon, pointArray, error)) {
            error.key = "lights.point";
            return false;
        }

        std::size_t scan = 0;
        while (true) {
            std::string lightObj;
            if (!JsonHelper::nextObjectInArray(pointArray, scan, lightObj, error))
                break;

            ParsedPointLight pl;

            // position x,y,z
            std::size_t xPos = lightObj.find("\"x\"");
            std::size_t yPos = lightObj.find("\"y\"");
            std::size_t zPos = lightObj.find("\"z\"");
            if (xPos == std::string::npos || yPos == std::string::npos || zPos == std::string::npos) {
                error.message = "point light must contain x, y, z";
                error.key = "lights.point";
                return false;
            }

            std::size_t xColon = lightObj.find(':', xPos) + 1;
            std::size_t yColon = lightObj.find(':', yPos) + 1;
            std::size_t zColon = lightObj.find(':', zPos) + 1;

            if (!JsonHelper::tryExtractJsonNumber(lightObj, xColon, pl.position.x, error)) return false;
            if (!JsonHelper::tryExtractJsonNumber(lightObj, yColon, pl.position.y, error)) return false;
            if (!JsonHelper::tryExtractJsonNumber(lightObj, zColon, pl.position.z, error)) return false;

            // intensity
            pl.intensity = 1.0;
            std::size_t iPos = lightObj.find("\"intensity\"");
            if (iPos != std::string::npos) {
                std::size_t iColon = lightObj.find(':', iPos) + 1;
                if (!JsonHelper::tryExtractJsonNumber(lightObj, iColon, pl.intensity, error)) {
                    error.key = "lights.point.intensity";
                    return false;
                }
                if (pl.intensity < 0.0 || pl.intensity > 1.0) {
                    error.message = "point light intensity must be between 0.0 and 1.0";
                    error.key = "lights.point.intensity";
                    return false;
                }
            }

            parsed.pointLights.push_back(pl);
        }
    }

    return true;
}

}
}
