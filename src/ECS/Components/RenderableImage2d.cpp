/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableImage2d
*/

#include "ECS/Components/RenderableImage2d.hpp"

#include "ECS/ECSErrors.hpp"
#include "Graphic/RessourcesManager.hpp"

ecs::component::RenderableImage2d::RenderableImage2d(std::string_view imagePath) noexcept
{
    this->valid = true;
    this->texture = graphic::RessourcesManager::getTexture(imagePath.data());
}

ecs::component::RenderableImage2d::RenderableImage2d(RenderableImage2d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->texture = other.texture;
}

ecs::component::RenderableImage2d& ecs::component::RenderableImage2d::operator=(RenderableImage2d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->texture = other.texture;
    return *this;
}

const Texture2D& ecs::component::RenderableImage2d::getTexture() const
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable Image 2d", "Use of the object before a correct initialization");
    }
    return this->texture;
}

void ecs::component::RenderableImage2d::setTexture(std::string_view imagePath) noexcept
{
    this->valid = true;
    this->texture = graphic::RessourcesManager::getTexture(imagePath.data());
}

utils::Vector ecs::component::RenderableImage2d::getSize() const noexcept
{
    return {static_cast<float>(this->texture.width), static_cast<float>(this->texture.height)};
}
