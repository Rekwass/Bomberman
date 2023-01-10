/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Redirect
*/

#include "Redirect.hpp"

std::ostream& operator<<(std::ostream& out, utils::Vector vector)
{
    out << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";
    return out;
}

std::ostream& operator<<(std::ostream& out, Vector3 vector)
{
    out << "{" << vector.x << ", " << vector.y << ", " << vector.z << "}";
    return out;
}
