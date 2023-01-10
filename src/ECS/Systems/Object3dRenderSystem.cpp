/*
** EPITECH PROJECT, 2022
** Object Render System
** File description:
** Object Render System
*/

#include "ECS/Systems/Object3dRenderSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Core/Coordinator.hpp"

void ecs::system::Object3dRenderSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& model = coordinator.getComponent<ecs::component::RenderableObject3d>(entity);
        Model m = model.getModel();

        DrawModelEx(m, attributes.position, attributes.rotationAxis, attributes.rotationAngle, {attributes.scale, attributes.scale, attributes.scale}, WHITE);
    }
}
