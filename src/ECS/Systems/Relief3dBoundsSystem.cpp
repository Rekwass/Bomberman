/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Relief3dBoundsSystem
*/

#include "ECS/Systems/Relief3dBoundsSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableRelief3d.hpp"

void ecs::system::Relief3dBoundsSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& model = coordinator.getComponent<ecs::component::RenderableRelief3d>(entity);
        auto& bounds = coordinator.getComponent<ecs::component::Bounds3d>(entity);

        bounds = GetMeshBoundingBox(model.getModel().meshes[0]);
        bounds.min.x += attributes.position.x;
        bounds.min.y += attributes.position.y;
        bounds.min.z += attributes.position.z;
        bounds.max.x += attributes.position.x;
        bounds.max.y += attributes.position.y;
        bounds.max.z += attributes.position.z;
    }
}
