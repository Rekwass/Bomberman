/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableText2d
*/

#pragma once

#include "raylib.h"

#include <string>

namespace ecs::component {

struct RenderableText2d {
    std::string text{};
    float fontSize = 10;
    Color color = WHITE;
};

} // namespace ecs::component
