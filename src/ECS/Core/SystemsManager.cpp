/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** SystemsManager
*/

#include "ECS/Core/SystemsManager.hpp"

#include "ECS/Core/Entities.hpp"

void ecs::SystemsManager::entitySignatureChanged(
    ecs::Entity entity, ecs::ComponentSignature signature) noexcept
{
    for (const auto& system : this->systems) {
        if ((signature & this->systemsSignatures[system.first]) == this->systemsSignatures[system.first]) {
            system.second->addEntity(entity);
        } else {
            system.second->removeEntity(entity);
        }
    }
}
