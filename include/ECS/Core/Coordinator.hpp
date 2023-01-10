/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Coordinator
*/

#pragma once

#include "ECS/Core/ComponentsManager.hpp"
#include "ECS/Core/EntitiesManager.hpp"
#include "ECS/Core/EventsManager.hpp"
#include "ECS/Core/SystemsManager.hpp"
#include "fmt/core.h"

namespace ecs {

/*
 * ECS coordinator
 */
class Coordinator {
   public:
    Coordinator() noexcept = default;
    Coordinator(Coordinator const& other) noexcept = delete;
    Coordinator(Coordinator&& other) noexcept = default;
    ~Coordinator() noexcept = default;

    Coordinator& operator=(Coordinator const& other) noexcept = delete;
    Coordinator& operator=(Coordinator&& other) noexcept = default;

    /*
     * Create a new entity
     *
     * Return the newly created entity
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
     * Register a new component to the manager
     *
     * No return value
     */
    template <typename T>
    void registerComponent()
    {
        this->componentsManager.registerComponent<T>();
    }
    /*
     * Get the specified component type
     *
     * Return the type of the component
     */
    template <typename T>
    ComponentType getComponentType() const
    {
        return this->componentsManager.getComponentType<T>();
    }
    /*
     * Set a component for an entity
     *
     * No return value
     *
     * entity -> The entity to set component for
     *
     * component -> The component to set
     */
    template <typename T>
    void setComponent(Entity entity, T component)
    {
        this->componentsManager.setComponent<T>(entity, std::forward<T>(component));

        auto signature = this->entitiesManager.getSignature(entity);
        signature.set(this->componentsManager.getComponentType<T>(), true);
        this->entitiesManager.setSignature(entity, signature);

        this->systemsManager.entitySignatureChanged(entity, signature);
    }
    /*
     * Remove a component for an entity
     *
     * No return value
     *
     * entity -> The entity to remove component for
     *
     * component -> The component to remove
     */
    template <typename T>
    void removeComponent(Entity entity)
    {
        auto signature = this->entitiesManager.getSignature(entity);
        signature.set(this->componentsManager.getComponentType<T>(), false);
        this->entitiesManager.setSignature(entity, signature);

        this->systemsManager.entitySignatureChanged(entity, signature);
    }
    /*
     * Get the component associated to the given entity
     *
     * Return a reference to the component
     *
     * entity -> The entity to get the associated component
     */
    template <typename T>
    T& getComponent(Entity entity)
    {
        return this->componentsManager.getComponent<T>(entity);
    }

    /*
     * Register a new system in the manager
     *
     * Return a reference to the newly created system
     *
     * NOTE: This automatically set the system signature by the types given in the template
     */
    template <typename T, typename... Arg>
    T& registerSystem()
    {
        auto& system = this->systemsManager.registerSystem<T>();

        ComponentSignature signature;
        ((signature.set(this->getComponentType<Arg>())), ...);
        this->systemsManager.setSystemSignature<T>(signature);

        return system;
    }

    /*
     * Call all listeners functions associated to the given event
     *
     * No return value
     *
     * event -> The event to call associated listeners
     */
    void sendEvent(const Events& event) noexcept;
    /*
     * Call all listeners functions associated to the given events
     *
     * No return value
     *
     * events -> The events to call associated listeners
     */
    void sendEvents(const std::vector<Events>& events) noexcept;
    /*
     * Add a listener function to call when the given event occurred
     *
     * No return value
     *
     * event -> The event the listener will be associated with
     *
     * f -> The function to call
     *
     * args -> The arguments to pass to the function
     */
    template <typename F, typename... Args>
    void addEventListener(const Events& event, F&& f, Args&&... args) noexcept
    {
        this->eventsManager.addListener(event, std::forward<F>(f),
            std::forward<Args>(args)...);
    }
    /*
     * Add a listener function to call when the given event occurred
     *
     * No return value
     *
     * events -> The events the listener will be associated with
     *
     * f -> The function to call
     *
     * args -> The arguments to pass to the function
     */
    template <typename F, typename... Args>
    void addEventListener(const std::vector<Events>& events, F&& f,
        Args&&... args) noexcept
    {
        for (const auto& event : events) {
            this->addEventListener(event, std::forward<F>(f),
                std::forward<Args>(args)...);
        }
    }
    /*
     * Remove all the listeners associated to an event
     *
     * No return value
     *
     * event -> The event to unassociate all listeners
     */
    void removeEventListeners(const Events& event) noexcept;
    /*
     * Remove all the listeners associated to multiple events
     *
     * No return value
     *
     * events -> The events to unassociate all listeners
     */
    void removeEventListeners(const std::vector<Events>& events) noexcept;

   private:
    EntitiesManager entitiesManager;
    ComponentsManager componentsManager;
    SystemsManager systemsManager;
    EventsManager eventsManager;
};

} // namespace ecs
