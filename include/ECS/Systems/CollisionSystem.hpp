/*
** EPITECH PROJECT, 2022
** Collision System
** File description:
** Create Collision System
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/System.hpp"

namespace ecs::system {

/*
 * Updator for the collisions
 */
class CollisionSystem final : public System {
   public:
    CollisionSystem() noexcept = default;
    CollisionSystem(CollisionSystem const& other) noexcept = default;
    CollisionSystem(CollisionSystem&& other) noexcept = default;
    ~CollisionSystem() noexcept final = default;

    CollisionSystem& operator=(CollisionSystem const& other) noexcept = default;
    CollisionSystem& operator=(CollisionSystem&& other) noexcept = default;

    /*
     * Remove an entity from to the system
     *
     * No return value
     *
     * entity -> The entity to remove from the system
     */
    void removeEntity(Entity entity) noexcept final;

    /*
     * Set the entity as a non-moving object
     *
     * No return value
     *
     * entity -> The entity to set non-moving
     */
    void setEntityNotMoving(ecs::Entity entity) noexcept;
    /*
     * Update the entities linked to the system
     *
     * No return value
     *
     * coordinator -> The coordinator to use to update the system
     */
    void update(Coordinator& coordinator, float dt) const noexcept;

   private:
    std::set<Entity> notMovingEntities;
};

} // namespace ecs::system
