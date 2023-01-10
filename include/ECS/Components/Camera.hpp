/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Camera
*/

#pragma once

#include "raylib.h"

namespace ecs::component {

struct Camera {
    Camera3D camera{};
    bool usingSpecialMode = false;
};

} // namespace ecs::component
