/*
** EPITECH PROJECT, 2026
** SphereParser
** File description:
** Internal declaration for sphere JSON object parsing
*/
#pragma once

#include <string>
#include "SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseSphere(const std::string &sphereObj, ParsedSphere &sphere,
                 SceneParseError &error);

}
}
}
