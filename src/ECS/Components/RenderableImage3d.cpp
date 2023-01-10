/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableImage3d
*/

#include "ECS/Components/RenderableImage3d.hpp"

#include "ECS/ECSErrors.hpp"
#include "Graphic/RessourcesManager.hpp"

ecs::component::RenderableImage3d::RenderableImage3d(std::string_view imagePath) noexcept
{
    this->valid = true;
    this->texture = graphic::RessourcesManager::getTexture(imagePath.data());
}

ecs::component::RenderableImage3d::RenderableImage3d(RenderableImage3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->texture = other.texture;
}

ecs::component::RenderableImage3d& ecs::component::RenderableImage3d::operator=(RenderableImage3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->texture = other.texture;
    return *this;
}

const Texture2D& ecs::component::RenderableImage3d::getTexture() const
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable Image 3d", "Use of the object before a correct initialization");
    }
    return this->texture;
}

void ecs::component::RenderableImage3d::setTexture(std::string_view imagePath) noexcept
{
    this->valid = true;
    this->texture = graphic::RessourcesManager::getTexture(imagePath.data());
}
