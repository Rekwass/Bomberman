/*
** EPITECH PROJECT, 2022
** include
** File description:
** Entities
*/

#pragma once

#include "ECS/Core/Components.hpp"

#include <cstdint>

namespace ecs {

using Entity = std::uint32_t;

constexpr Entity MAX_ENTITIES = 1024;

} // namespace ecs
