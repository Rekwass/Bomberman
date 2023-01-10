/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** AnimationSystem
*/

#include "ECS/Systems/AnimationSystem.hpp"

#include "ECS/Components/Animation.hpp"
#include "ECS/Components/RenderableObject3d.hpp"

void ecs::system::AnimationSystem::update(ecs::Coordinator& coordinator, float elapsedTime) const
{
    // TODO: problem ici pour windows
    for (const auto& entity : this->entities) {
        auto& object = coordinator.getComponent<ecs::component::RenderableObject3d>(entity);
        auto& animation = coordinator.getComponent<ecs::component::Animation>(entity);
        animation.update(object.getModel(), elapsedTime);
    }
}
