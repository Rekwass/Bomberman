/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** EntitiesManager
*/

#include "ECS/Core/EntitiesManager.hpp"

#include "ECS/ECSErrors.hpp"

ecs::EntitiesManager::EntitiesManager() noexcept
{
    for (ecs::Entity entity = 0; entity < ecs::MAX_ENTITIES; entity++) {
        this->availableEntities.insert(entity);
    }
}

ecs::Entity ecs::EntitiesManager::createEntity()
{
    if (this->availableEntities.empty()) {
        throw error::ECSError("Too many entities in existence, cannot create a new one");
    }

    Entity entity = this->availableEntities.extract(this->availableEntities.begin()).value();

    return entity;
}

void ecs::EntitiesManager::destroyEntity(ecs::Entity entity) noexcept
{
    if (entity < MAX_ENTITIES and not this->availableEntities.contains(entity)) {
        this->entitiesSignatures.at(entity).reset();
        this->availableEntities.insert(entity);
    }
}

void ecs::EntitiesManager::setSignature(ecs::Entity entity, ecs::ComponentSignature signature)
{
    if (entity >= MAX_ENTITIES) {
        throw error::ECSError("Entity out of range");
    }

    this->entitiesSignatures.at(entity) = signature;
}

ecs::ComponentSignature ecs::EntitiesManager::getSignature(ecs::Entity entity) const
{
    if (entity >= MAX_ENTITIES) {
        throw error::ECSError("Entity out of range");
    }

    return this->entitiesSignatures.at(entity);
}
