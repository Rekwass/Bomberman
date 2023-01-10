/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** CubicMap3dBoundsSystem
*/

#include "ECS/Systems/CubicMap3dBoundsSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableCubicMap3d.hpp"

void ecs::system::CubicMap3dBoundsSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& model = coordinator.getComponent<ecs::component::RenderableCubicMap3d>(entity);
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
