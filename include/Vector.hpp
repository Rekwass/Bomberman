/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Vector
*/

#pragma once

#include "raylib.h"

#include <functional>

namespace utils {

struct Vector {
    Vector operator+(Vector other) const noexcept;
    Vector operator+(float other) const noexcept;
    Vector operator-(Vector other) const noexcept;
    Vector operator-(float other) const noexcept;
    Vector operator*(Vector other) const noexcept;
    Vector operator*(float other) const noexcept;
    Vector operator/(Vector other) const noexcept;
    Vector operator/(float other) const noexcept;
    Vector& operator++() noexcept;
    Vector& operator--() noexcept;
    bool operator==(Vector const& other) const noexcept;
    bool operator!=(Vector const& other) const noexcept;
    bool operator>(Vector const& other) const noexcept;
    bool operator<(Vector const& other) const noexcept;
    bool operator>=(Vector const& other) const noexcept;
    bool operator<=(Vector const& other) const noexcept;
    bool operator!() const noexcept;
    Vector& operator+=(Vector other) noexcept;
    Vector& operator-=(Vector other) noexcept;
    Vector& operator*=(Vector other) noexcept;
    Vector& operator/=(Vector other) noexcept;

    // NOLINTNEXTLINE
    operator Vector3() const;

    float x = 0;
    float y = 0;
    float z = 0;
};

struct VectorHash {
    std::size_t operator()(const Vector& vector) const noexcept;
};

} // namespace utils
