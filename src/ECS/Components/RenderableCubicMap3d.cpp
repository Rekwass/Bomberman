/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableCubicMap3d
*/

#include "ECS/Components/RenderableCubicMap3d.hpp"

#include "ECS/ECSErrors.hpp"
#include "Graphic/RessourcesManager.hpp"

ecs::component::RenderableCubicMap3d::RenderableCubicMap3d(std::string_view mapPath, std::string_view atlasPath, utils::Vector size) noexcept
{
    this->valid = true;
    Image image = LoadImage(mapPath.data());
    Mesh mesh = GenMeshCubicmap(image, size);
    UnloadImage(image);
    this->model = LoadModelFromMesh(mesh);
    this->texture = graphic::RessourcesManager::getTexture(atlasPath.data());
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}

ecs::component::RenderableCubicMap3d::RenderableCubicMap3d(RenderableCubicMap3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->texture = other.texture;
}

ecs::component::RenderableCubicMap3d& ecs::component::RenderableCubicMap3d::operator=(RenderableCubicMap3d&& other) noexcept
{
    this->valid = other.valid;
    other.valid = false;
    this->model = other.model;
    this->texture = other.texture;
    return *this;
}

ecs::component::RenderableCubicMap3d::~RenderableCubicMap3d() noexcept
{
    if (this->valid) {
        UnloadModel(this->model);
    }
}

const Model& ecs::component::RenderableCubicMap3d::getModel() const
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable Cubicmap 3d", "Use of the object before a correct initialization");
    }
    return this->model;
}

void ecs::component::RenderableCubicMap3d::setMap(std::string_view mapPath, utils::Vector size)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable Cubicmap 3d", "Use of the object before a correct initialization");
    }
    if (this->valid) {
        UnloadModel(this->model);
        Image image = LoadImage(mapPath.data());
        Mesh mesh = GenMeshCubicmap(image, size);
        UnloadImage(image);
        this->model = LoadModelFromMesh(mesh);
    }
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}

void ecs::component::RenderableCubicMap3d::setTexture(std::string_view atlasPath)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Renderable Cubicmap 3d", "Use of the object before a correct initialization");
    }
    this->texture = graphic::RessourcesManager::getTexture(atlasPath.data());
    SetMaterialTexture(&this->model.materials[0], MATERIAL_MAP_DIFFUSE, this->texture);
}
