/*
** EPITECH PROJECT, 2022
** src
** File description:
** Wall
*/

#include "Game/Map/Items/Wall.hpp"

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"

game::Wall::Wall(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, std::string_view modelPath, std::string_view texturePath, const utils::Vector& position) :
    coordinator(coordinator), entity(coordinator.createEntity())
{
    this->coordinator.setComponent(this->entity, ecs::component::Attributes{.position = position});
    this->coordinator.setComponent(this->entity, std::move(ecs::component::RenderableObject3d(modelPath, texturePath)));
    this->coordinator.setComponent(this->entity, ecs::component::Bounds3d{});
    collisionSystem.setEntityNotMoving(this->entity);
}

game::Wall::Wall(Wall&& other) noexcept :
    coordinator(other.coordinator), entity(other.entity), valid(other.valid)
{
    other.valid = false;
}

game::Wall::~Wall()
{
    if (this->valid) {
        this->coordinator.destroyEntity(this->entity);
    }
}

utils::Vector game::Wall::getPosition() const noexcept
{
    return this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
}
