/*
** EPITECH PROJECT, 2022
** include
** File description:
** Components
*/

#pragma once

#include <bitset>

namespace ecs {

using ComponentType = std::uint8_t;

constexpr ComponentType MAX_COMPONENTS = 32;

using ComponentSignature = std::bitset<MAX_COMPONENTS>;

} // namespace ecs
