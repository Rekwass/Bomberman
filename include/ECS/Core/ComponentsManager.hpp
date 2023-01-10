/*
** EPITECH PROJECT, 2022
** include
** File description:
** ComponentsManager
*/

#pragma once

#include "ECS/Core/ComponentArray.hpp"
#include "ECS/Core/Components.hpp"
#include "ECS/Core/Utils.hpp"
#include "ECS/ECSErrors.hpp"
#include "fmt/core.h"

#include <memory>
#include <string_view>
#include <unordered_map>

namespace ecs {

/*
 * Manage different components
 */
class ComponentsManager {
   public:
    ComponentsManager() noexcept = default;
    ComponentsManager(ComponentsManager const& other) noexcept = delete;
    ComponentsManager(ComponentsManager&& other) noexcept = default;
    ~ComponentsManager() noexcept = default;

    ComponentsManager& operator=(ComponentsManager const& other) noexcept = delete;
    ComponentsManager& operator=(ComponentsManager&& other) noexcept = default;

    /*
     * Register a new component in the manager
     *
     * No return value
     */
    template <typename T>
    void registerComponent()
    {
        std::string_view tname = typeName<T>();

        if (this->componentsTypes.contains(tname)) {
            throw error::ECSError(
                fmt::format("Registering same component({}) two times", tname));
        }

        this->componentsTypes.insert({tname, this->nextType++});
        this->componentsArrays.insert(
            {tname, std::make_unique<ComponentArray<T>>()});
    }
    /*
     * Get a component type
     *
     * Return the component type associated with the type
     */
    template <typename T>
    ComponentType getComponentType() const
    {
        std::string_view tname = typeName<T>();

        if (not this->componentsTypes.contains(tname)) {
            throw error::ECSError(
                fmt::format("Component {} not registered before use", tname));
        }

        return this->componentsTypes.find(tname)->second;
    }
    /*
     * Set a component for an entity
     *
     * No return value
     *
     * entity -> The entity to set the component
     *
     * component -> The component to set
     */
    template <typename T>
    void setComponent(Entity entity, T component)
    {
        this->getComponentArray<T>().setComponent(entity, std::forward<T>(component));
    }
    /*
     * Get the component associated to the given entity
     *
     * Return a reference to the component
     *
     * entity -> The entity to get the component for
     */
    template <typename T>
    T& getComponent(Entity entity) const
    {
        return this->getComponentArray<T>().getComponent(entity);
    }

   private:
    /*
     * Get the component array associated with the given type
     *
     * Return the component array
     */
    template <typename T>
    ComponentArray<T>& getComponentArray() const
    {
        std::string_view tname = typeName<T>();

        if (not this->componentsTypes.contains(tname)) {
            throw error::ECSError(
                fmt::format("Component {} not registered before use", tname));
        }

        return dynamic_cast<ComponentArray<T>&>(
            *(this->componentsArrays.at(tname)));
    }

    std::unordered_map<std::string_view, ComponentType> componentsTypes;
    std::unordered_map<std::string_view, std::unique_ptr<IComponentArray>>
        componentsArrays;
    ComponentType nextType = 0;
};

} // namespace ecs
