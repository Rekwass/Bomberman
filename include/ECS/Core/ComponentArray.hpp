/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** ComponentArray
*/

#pragma once

#include "ECS/Core/Entities.hpp"
#include "ECS/ECSErrors.hpp"

#include <array>

namespace ecs {

/*
 * Component array template
 */
class IComponentArray {
   public:
    IComponentArray() noexcept = default;
    IComponentArray(IComponentArray const& other) noexcept = delete;
    IComponentArray(IComponentArray&& other) noexcept = default;
    virtual ~IComponentArray() noexcept = default;

    IComponentArray& operator=(IComponentArray const& other) noexcept = delete;
    IComponentArray& operator=(IComponentArray&& other) noexcept = default;
};

template <typename T>
/*
 * Component array
 */
class ComponentArray final : public IComponentArray {
   public:
    ComponentArray() noexcept = default;
    ComponentArray(ComponentArray const& other) noexcept = delete;
    ComponentArray(ComponentArray&& other) noexcept = default;
    ~ComponentArray() noexcept final = default;

    ComponentArray& operator=(ComponentArray const& other) noexcept = delete;
    ComponentArray& operator=(ComponentArray&& other) noexcept = default;

    /*
     * Set a component associated to the given entity
     *
     * No return value
     *
     * entity -> The entity to set the associated component
     *
     * component -> The component to set
     */
    void setComponent(Entity entity, T component)
    {
        if (entity >= MAX_ENTITIES) {
            throw error::ECSError("Use an out of range entity");
        }

        this->componentsArray[entity] = std::forward<T>(component);
    }
    /*
     * Get the component associated to the given entity
     *
     * Return the component
     *
     * entity -> The entity to get associated component
     */
    T& getComponent(Entity entity) noexcept
    {
        return this->componentsArray.at(entity);
    }

   private:
    std::array<T, MAX_ENTITIES> componentsArray;
};

} // namespace ecs
