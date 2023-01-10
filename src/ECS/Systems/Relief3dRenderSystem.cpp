/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Relief3dRenderSystem
*/

#include "ECS/Systems/Relief3dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableRelief3d.hpp"

void ecs::system::Relief3dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& relief = coordinator.getComponent<ecs::component::RenderableRelief3d>(entity);
        Model m = relief.getModel();
        Color c = relief.getColor();

        DrawModelEx(m, attributes.position, attributes.rotationAxis, attributes.rotationAngle, {attributes.scale, attributes.scale, attributes.scale}, c);
    }
}
