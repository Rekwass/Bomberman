/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** CubicMap3dRenderSystem
*/

#include "ECS/Systems/CubicMap3dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableCubicMap3d.hpp"

void ecs::system::CubicMap3dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& map = coordinator.getComponent<ecs::component::RenderableCubicMap3d>(entity);
        Model m = map.getModel();

        DrawModelEx(m, attributes.position, attributes.rotationAxis, attributes.rotationAngle, {attributes.scale, attributes.scale, attributes.scale}, WHITE);
    }
}
