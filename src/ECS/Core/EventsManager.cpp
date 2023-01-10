/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** EventsManager
*/

#include "ECS/Core/EventsManager.hpp"

void ecs::EventsManager::sendEvent(const ecs::Events& event) const noexcept
{
    if (this->listeners.contains(event)) {
        for (const auto& listener : this->listeners.at(event)) {
            (*listener)();
        }
    }
}

void ecs::EventsManager::removeListeners(const ecs::Events& event) noexcept
{
    if (this->listeners.contains(event)) {
        this->listeners.at(event).clear();
    }
}
