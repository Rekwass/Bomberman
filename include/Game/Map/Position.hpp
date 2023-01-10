/*
** EPITECH PROJECT, 2022
** include
** File description:
** Position
*/

#pragma once

#include <cstddef>

namespace game {

struct Position {
    bool operator==(const Position& other) const noexcept;

    int x = 0;
    int y = 0;
};

struct PositionHash {
    std::size_t operator()(const Position& obj) const noexcept;
};

} // namespace game
