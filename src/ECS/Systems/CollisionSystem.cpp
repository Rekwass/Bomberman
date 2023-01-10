/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** Collisions System
*/

#include "ECS/Systems/CollisionSystem.hpp"

#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/Transform.hpp"
#include "Graphic/HitboxDisplayer.hpp"

void ecs::system::CollisionSystem::removeEntity(Entity entity) noexcept
{
    this->entities.erase(entity);
    this->notMovingEntities.erase(entity);
}

void ecs::system::CollisionSystem::setEntityNotMoving(ecs::Entity entity) noexcept
{
    this->entities.erase(entity);
    this->notMovingEntities.insert(entity);
}

void ecs::system::CollisionSystem::update(ecs::Coordinator& coordinator, float dt) const noexcept
{
    // Reset all collisions
    for (const auto& entity : this->entities) {
        auto& transform = coordinator.getComponent<ecs::component::Transform>(entity);
        transform.movingX = true;
        transform.movingY = true;
        transform.movingZ = true;
    }

    // NOLINTNEXTLINE
    for (auto it = this->entities.begin(); it != this->entities.end(); it++) {
        auto& transform1 = coordinator.getComponent<ecs::component::Transform>(*it);
        auto movement1 = transform1.movement * dt;
        auto bounds1 = coordinator.getComponent<ecs::component::Bounds3d>(*it);
        auto bounds1X = coordinator.getComponent<ecs::component::Bounds3d>(*it);
        auto bounds1Y = coordinator.getComponent<ecs::component::Bounds3d>(*it);
        auto bounds1Z = coordinator.getComponent<ecs::component::Bounds3d>(*it);

        bounds1X.min.x += movement1.x;
        bounds1X.max.x += movement1.x;
        bounds1Y.min.y += movement1.y;
        bounds1Y.max.y += movement1.y;
        bounds1Z.min.z += movement1.z;
        bounds1Z.max.z += movement1.z;

        // Check collisions with non-moving entities
        for (const auto& entity : this->notMovingEntities) {
            auto bounds2 = coordinator.getComponent<ecs::component::Bounds3d>(entity);

            if (not CheckCollisionBoxes(bounds1, bounds2)) {
                if (CheckCollisionBoxes(bounds1X, bounds2)) {
                    graphic::HitboxDisplayer::addPrevisualization(*it, bounds1X);
                    graphic::HitboxDisplayer::setHitBoxInCollision(*it);
                    graphic::HitboxDisplayer::setHitBoxInCollisionNotMoving(entity);
                    transform1.movingX = false;
                }
                if (CheckCollisionBoxes(bounds1Y, bounds2)) {
                    graphic::HitboxDisplayer::addPrevisualization(*it, bounds1Y);
                    graphic::HitboxDisplayer::setHitBoxInCollision(*it);
                    graphic::HitboxDisplayer::setHitBoxInCollisionNotMoving(entity);
                    transform1.movingY = false;
                }
                if (CheckCollisionBoxes(bounds1Z, bounds2)) {
                    graphic::HitboxDisplayer::addPrevisualization(*it, bounds1Z);
                    graphic::HitboxDisplayer::setHitBoxInCollision(*it);
                    graphic::HitboxDisplayer::setHitBoxInCollisionNotMoving(entity);
                    transform1.movingZ = false;
                }
            }
        }
    }
}
