/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** ECSErrors
*/

#include "ECS/ECSErrors.hpp"

ecs::error::ECSError::ECSError(std::string const& message) :
    message(message) { }

const char* ecs::error::ECSError::what() const noexcept
{
    return this->message.c_str();
}

ecs::error::ComponentError::ComponentError(std::string const& name, std::string const& message) :
    ECSError(message), name(name) { }

const char* ecs::error::ComponentError::which() const noexcept
{
    return this->name.c_str();
}
