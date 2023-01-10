/*
** EPITECH PROJECT, 2022
** System
** File description:
** System
*/

#pragma once

#include "ECS/Core/Entities.hpp"

#include <set>

namespace ecs {

/*
 * System template
 */
class System {
   public:
    System() noexcept = default;
    System(System const& other) noexcept = default;
    System(System&& other) noexcept = default;
    virtual ~System() noexcept = default;

    System& operator=(System const& other) noexcept = default;
    System& operator=(System&& other) noexcept = default;

    /*
     * Add an entity to the system
     *
     * No return value
     *
     * entity -> The entity to add to the system
     */
    virtual void addEntity(Entity entity) noexcept;
    /*
     * Remove an entity from to the system
     *
     * No return value
     *
     * entity -> The entity to remove from the system
     */
    virtual void removeEntity(Entity entity) noexcept;

   protected:
    std::set<Entity> entities;
};

} // namespace ecs