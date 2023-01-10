/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** Camera System
*/

#include "ECS/Systems/CameraSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Camera.hpp"

void ecs::system::CameraSystem::update(
    ecs::Coordinator& coordinator) const noexcept
{
    for (const auto& entity : this->entities) {
        auto& attribute = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& camera = coordinator.getComponent<ecs::component::Camera>(entity);

        if (not camera.usingSpecialMode) {
            camera.camera.position = attribute.position;
        }

        UpdateCamera(&camera.camera);
    }
}
