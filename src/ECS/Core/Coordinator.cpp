/*
** EPITECH PROJECT, 2022
** Coordinator
** File description:
** Coordinator
*/

#include "ECS/Core/Coordinator.hpp"

ecs::Entity ecs::Coordinator::createEntity()
{
    return this->entitiesManager.createEntity();
}

void ecs::Coordinator::destroyEntity(ecs::Entity entity) noexcept
{
    this->systemsManager.entitySignatureChanged(entity, ComponentSignature{});
    this->entitiesManager.destroyEntity(entity);
}

void ecs::Coordinator::sendEvent(const Events& event) noexcept
{
    this->eventsManager.sendEvent(event);
}

void ecs::Coordinator::sendEvents(const std::vector<Events>& events) noexcept
{
    for (const auto& event : events) {
        this->sendEvent(event);
    }
}

void ecs::Coordinator::removeEventListeners(const Events& event) noexcept
{
    this->eventsManager.removeListeners(event);
}

void ecs::Coordinator::removeEventListeners(const std::vector<Events>& events) noexcept
{
    for (const auto& event : events) {
        this->removeEventListeners(event);
    }
}
