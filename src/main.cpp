/*
** EPITECH PROJECT, 2026
** raytracer
** File description:
** main
*/
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace {

constexpr int success_exit_code = 0;
constexpr int error_exit_code = 84;

int print_error(const std::string &message)
{
    std::cerr << message << '\n';
    return error_exit_code;
}

int print_help()
{
    std::cout << "USAGE: ./raytracer <SCENE_FILE>\n"
              << "  SCENE_FILE: scene configuration\n";
    return success_exit_code;
}

bool scene_file_exists(const std::string &path)
{
    std::error_code errorCode;
    const std::filesystem::path scenePath(path);

    return std::filesystem::exists(scenePath, errorCode)
        && std::filesystem::is_regular_file(scenePath, errorCode)
        && !errorCode;
}

} // namespace

int main(int argc, char **argv)
{
    if (argc == 2 && std::string(argv[1]) == "--help")
        return print_help();

    if (argc != 2)
        return print_error("error: invalid args, use --help or provide one scene file.");

    const std::string sceneFile = argv[1];
    if (!scene_file_exists(sceneFile))
        return print_error("error: scene file not found: " + sceneFile);

    std::ifstream input(sceneFile);
    if (!input.is_open())
        return print_error("error: unable to open scene file: " + sceneFile);

    return success_exit_code;
}