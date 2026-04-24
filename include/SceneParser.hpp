/*
** EPITECH PROJECT, 2026
** SceneParser
** File description:
** SceneParser
*/
#pragma once

#include <cstddef>
#include <string>
#include <vector>
#include "Camera.hpp"

namespace RayTracer {

class ParsedScene {
public:
    std::string rawContent;
    std::vector<std::string> topLevelKeys;
    Camera camera;
    // more fields will be added: lights, primitives
};

class SceneParseError {
public:
    std::string message;
    std::size_t line = 1;
    std::size_t column = 1;
    std::string key;

    std::string toString() const;
};

class SceneParseResult {
public:
    bool ok = false;
    ParsedScene scene;
    SceneParseError error;
};

class SceneParser {
public:
    static SceneParseResult parseFile(const std::string &path);
    static SceneParseResult parseText(const std::string &content);
};

}