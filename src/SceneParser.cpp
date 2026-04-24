/*
** EPITECH PROJECT, 2026
** SceneParser
** File description:
** SceneParser
*/

#include "SceneParser.hpp"


#include <cctype>
#include <fstream>
#include <sstream>

namespace RayTracer {

namespace {

struct Cursor {
    std::size_t line = 1;
    std::size_t column = 1;
};

bool is_whitespace(char c)
{
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

std::size_t skip_whitespace(const std::string &content, std::size_t index)
{
    while (index < content.size() && is_whitespace(content[index]))
        ++index;
    return index;
}

}

std::string SceneParseError::toString() const
{
    std::ostringstream stream;

    stream << "scene parse error at line " << line << ", column " << column;
    if (!key.empty())
        stream << " near key '" << key << "'";
    stream << ": " << message;
    return stream.str();
}

SceneParseResult SceneParser::parseFile(const std::string &path)
{
    std::ifstream input(path);
    SceneParseResult result;

    if (!input.is_open()) {
        result.ok = false;
        result.error.message = "unable to open scene file: " + path;
        return result;
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    return parseText(buffer.str());
}
