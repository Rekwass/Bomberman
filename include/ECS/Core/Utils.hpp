/*
** EPITECH PROJECT, 2022
** include
** File description:
** Utils
*/

#pragma once

#include <memory>
#include <string_view>

namespace ecs {

template <typename T>
std::string_view typeName()
{
    return typeid(T).name();
}

} // namespace ecs
