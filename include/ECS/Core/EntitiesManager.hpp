/*
** EPITECH PROJECT, 2022
** include
** File description:
** EntitiesManager
*/

#pragma once

#include "ECS/Core/Entities.hpp"

#include <array>
#include <cstdint>
#include <set>

namespace ecs {

/*
 * Manage entities for ecs
 */
class EntitiesManager {
   public:
    EntitiesManager() noexcept;
    EntitiesManager(EntitiesManager const& other) noexcept = delete;
    EntitiesManager(EntitiesManager&& other) noexcept = default;
    ~EntitiesManager() noexcept = default;

    EntitiesManager& operator=(EntitiesManager const& other) noexcept = delete;
    EntitiesManager& operator=(EntitiesManager&& other) noexcept = default;

    /*
     * Get a new entity
     *
     * Return the entity
     */
    Entity createEntity();
    /*
     * Destroy an existing entity
     *
     * No return value
     *
     * entity -> The entity to destroy
     */
    void destroyEntity(Entity entity) noexcept;
    /*
     * Set the signature of an entity
     *
     * No return value
     *
     * entity -> The entity to set the signature for
     *
     * signature -> The signature to set
     */
    void setSignature(Entity entity, ComponentSignature signature);
    /*
     * Get the signature of an entity
     *
     * Return the signature of the entity
     *
     * entity -> The entity to get signature of
     */
    ComponentSignature getSignature(Entity entity) const;

   private:
    std::set<Entity> availableEntities;
    std::array<ComponentSignature, MAX_ENTITIES> entitiesSignatures;
};

} // namespace ecs
