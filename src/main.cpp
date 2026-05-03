/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/
#include <filesystem>
#include <iostream>
#include <string>

#include "SceneParser.hpp"
#include "SceneLoader.hpp"
#include "Renderer.hpp"

namespace {

int print_error(const std::string &message)
{
    std::cerr << message << '\n';
    return 84;
}

int print_help()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n"
              << "  SCENE_FILE: scene configuration\n";
    return 0;
}

bool scene_file_exists(const std::string &path)
{
    std::error_code errorCode;
    const std::filesystem::path scenePath(path);

    return std::filesystem::exists(scenePath, errorCode)
        && std::filesystem::is_regular_file(scenePath, errorCode)
        && !errorCode;
}

}

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "--help")
        return print_help();

    if (argc != 2)
        return print_error("error: invalid args, use --help or provide one scene file");

    const std::string sceneFile = argv[1];
    if (!scene_file_exists(sceneFile))
        return print_error("error: scene file not found: " + sceneFile);

    const RayTracer::SceneParseResult parseResult = RayTracer::SceneParser::parseFile(sceneFile);
    if (!parseResult.ok)
        return print_error("error: " + parseResult.error.toString());

    const RayTracer::Scene scene = RayTracer::SceneLoader::load(parseResult.scene);

    const std::string outputPath = "output.ppm";
    std::cout << "rendering " << scene.camera.resolutionWidth << "x"
              << scene.camera.resolutionHeight << " ... ";
    std::cout.flush();

    RayTracer::Renderer::render(scene, outputPath);

    std::cout << "done -> " << outputPath << "\n";
    return 0;
}