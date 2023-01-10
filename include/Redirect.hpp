/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Redirect
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <ostream>

std::ostream& operator<<(std::ostream& out, utils::Vector vector);
std::ostream& operator<<(std::ostream& out, Vector3 vector);
