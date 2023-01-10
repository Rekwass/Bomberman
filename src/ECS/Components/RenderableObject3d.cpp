/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableObject3d
*/

#include "ECS/Components/RenderableObject3d.hpp"

#include "ECS/ECSErrors.hpp"
#include "Graphic/RessourcesManager.hpp"

ecs::component::RenderableObject3d::RenderableObject3d(std::string_view modelPath, std::string_view texturePath) noexcept
{
    this->valid = true;
    this->model = LoadModel(modelPath.data());
    this->texture = graphic::RessourcesManager::getTexture(texturePath.data());
    // this->texture = LoadTexture(texturePath.data());
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}

ecs::component::RenderableObject3d::RenderableObject3d(RenderableObject3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->texture = other.texture;
}

ecs::component::RenderableObject3d& ecs::component::RenderableObject3d::operator=(RenderableObject3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->texture = other.texture;
    return *this;
}

ecs::component::RenderableObject3d::~RenderableObject3d() noexcept
{
    if (this->valid) {
        UnloadModel(this->model);
    }
}

const Model& ecs::component::RenderableObject3d::getModel() const
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable object 3d", "Use of the object before a correct initialization");
    }
    return this->model;
}

void ecs::component::RenderableObject3d::setModel(std::string_view modelPath)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable object 3d", "Use of the object before a correct initialization");
    }
    UnloadModel(this->model);
    this->model = LoadModel(modelPath.data());
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}

void ecs::component::RenderableObject3d::setTexture(std::string_view texturePath)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable object 3d", "Use of the object before a correct initialization");
    }
    this->texture = graphic::RessourcesManager::getTexture(texturePath.data());
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}
