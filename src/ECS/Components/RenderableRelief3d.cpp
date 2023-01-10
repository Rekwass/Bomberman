/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableRelief3d
*/

#include "ECS/Components/RenderableRelief3d.hpp"

ecs::component::RenderableRelief3d::RenderableRelief3d(std::string_view reliefPath, utils::Vector size, Color color) noexcept
{
    this->valid = true;
    this->color = color;
    Image image = LoadImage(reliefPath.data());
    Mesh mesh = GenMeshHeightmap(image, size);
    this->model = LoadModelFromMesh(mesh);
    this->relief = LoadTextureFromImage(image);
    UnloadImage(image);
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->relief);
}

ecs::component::RenderableRelief3d::RenderableRelief3d(RenderableRelief3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->relief = other.relief;
    this->color = other.color;
}

ecs::component::RenderableRelief3d& ecs::component::RenderableRelief3d::operator=(RenderableRelief3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->relief = other.relief;
    this->color = other.color;
    return *this;
}

ecs::component::RenderableRelief3d::~RenderableRelief3d() noexcept
{
    if (this->valid) {
        UnloadModel(this->model);
        UnloadTexture(this->relief);
    }
}

const Model& ecs::component::RenderableRelief3d::getModel() const noexcept
{
    return this->model;
}

const Color& ecs::component::RenderableRelief3d::getColor() const noexcept
{
    return this->color;
}

void ecs::component::RenderableRelief3d::setColor(Color color) noexcept
{
    this->color = color;
}

void ecs::component::RenderableRelief3d::setRelief(std::string_view reliefPath, utils::Vector size, Color color) noexcept
{
    if (this->valid) {
        UnloadModel(this->model);
        UnloadTexture(this->relief);
    }
    this->valid = true;
    Image image = LoadImage(reliefPath.data());
    Mesh mesh = GenMeshHeightmap(image, size);
    this->model = LoadModelFromMesh(mesh);
    this->relief = LoadTextureFromImage(image);
    UnloadImage(image);
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->relief);
    this->color = color;
}
