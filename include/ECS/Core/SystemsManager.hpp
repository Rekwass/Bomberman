/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** SystemsManager
*/

#pragma once

#include "ECS/Core/Components.hpp"
#include "ECS/Core/System.hpp"
#include "ECS/Core/Utils.hpp"
#include "ECS/ECSErrors.hpp"
#include "fmt/core.h"

#include <memory>
#include <string_view>
#include <unordered_map>

namespace ecs {

/*
 * Manage different systems
 */
class SystemsManager {
   public:
    SystemsManager() noexcept = default;
    SystemsManager(SystemsManager const& other) noexcept = delete;
    SystemsManager(SystemsManager&& other) noexcept = default;
    ~SystemsManager() noexcept = default;

    SystemsManager& operator=(SystemsManager const& other) noexcept = delete;
    SystemsManager& operator=(SystemsManager&& other) noexcept = default;

    /*
     * Register a new system in the manager
     *
     * Return a reference to the newly created system
     */
    template <typename T>
    T& registerSystem()
    {
        std::string_view tname = typeName<T>();

        if (this->systems.contains(tname)) {
            throw error::ECSError(
                fmt::format("Registering same system({}) two times", tname));
        }

        this->systems.insert({tname, std::make_unique<T>()});
        return dynamic_cast<T&>(*(this->systems.at(tname)));
    }
    /*
     * Set a new components' signature for a system
     *
     * No return value
     *
     * signature -> The new signature to set
     */
    template <typename T>
    void setSystemSignature(ComponentSignature signature)
    {
        std::string_view tname = typeName<T>();

        if (not this->systems.contains(tname)) {
            throw error::ECSError(
                fmt::format("System {} not registered before use", tname));
        }

        this->systemsSignatures[tname] = signature;
    }
    /*
     * Notify each system that an entity signature has changed
     *
     * No return value
     *
     * entity -> The entity that has it signature changed
     *
     * signature -> The new entity signature
     */
    void entitySignatureChanged(Entity entity, ComponentSignature signature) noexcept;

   private:
    std::unordered_map<std::string_view, ComponentSignature> systemsSignatures;
    std::unordered_map<std::string_view, std::unique_ptr<System>> systems;
};

} // namespace ecs
