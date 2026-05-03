/*
** EPITECH PROJECT, 2026
** CylinderParser
** File description:
** internal declaration for cylinder json object parsing
*/
#pragma once

#include <string>
#include "SceneParser.hpp"

namespace RayTracer {
namespace Parser {
namespace Primitives {

bool parseCylinder(const std::string &cylObj, ParsedCylinder &cyl,
                   SceneParseError &error);

}
}
}
