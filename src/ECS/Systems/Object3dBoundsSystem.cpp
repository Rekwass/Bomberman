/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Object3dBoundsSystem
*/

#include "ECS/Systems/Object3dBoundsSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "Graphic/HitboxDisplayer.hpp"

void ecs::system::Object3dBoundsSystem::update(ecs::Coordinator& coordinator) const
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& model = coordinator.getComponent<ecs::component::RenderableObject3d>(entity);
        auto& bounds = coordinator.getComponent<ecs::component::Bounds3d>(entity);

        bounds = GetModelBoundingBox(model.getModel());
        bounds.min.x += attributes.position.x;
        bounds.min.y += attributes.position.y;
        bounds.min.z += attributes.position.z;
        bounds.max.x += attributes.position.x;
        bounds.max.y += attributes.position.y;
        bounds.max.z += attributes.position.z;
        graphic::HitboxDisplayer::addHitbox(entity, bounds);
    }
}
