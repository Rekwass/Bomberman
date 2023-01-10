/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** TransformSystem
*/

#include "ECS/Systems/TransformSystem.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Transform.hpp"
#include "Vector.hpp"

void ecs::system::TransformSystem::update(ecs::Coordinator& coordinator, float elapsedTime) const noexcept
{
    for (const auto& entity : this->entities) {
        auto& attributes = coordinator.getComponent<ecs::component::Attributes>(entity);
        auto& transform = coordinator.getComponent<ecs::component::Transform>(entity);

        if (attributes.rotationAngle != transform.rotationAngleGoal) {
            float trans = transform.rotationSpeed * elapsedTime;

            if (attributes.rotationAngle > transform.rotationAngleGoal) {
                if (attributes.rotationAngle - transform.rotationAngleGoal <= trans) {
                    attributes.rotationAngle = transform.rotationAngleGoal;
                } else {
                    attributes.rotationAngle -= trans;
                }
            } else {
                if (transform.rotationAngleGoal - attributes.rotationAngle <= trans) {
                    attributes.rotationAngle = transform.rotationAngleGoal;
                } else {
                    attributes.rotationAngle += trans;
                }
            }
        }

        attributes.position += utils::Vector{(transform.movingX ? transform.movement.x : 0), (transform.movingY ? transform.movement.y : 0), (transform.movingZ ? transform.movement.z : 0)} * elapsedTime;
    }
}
