/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** System
*/

#include "ECS/Core/System.hpp"

void ecs::System::addEntity(Entity entity) noexcept
{
    this->entities.insert(entity);
}

void ecs::System::removeEntity(Entity entity) noexcept
{
    this->entities.erase(entity);
}
