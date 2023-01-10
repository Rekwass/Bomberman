/*
** EPITECH PROJECT, 2022
** src
** File description:
** Bomb
*/

#include "Game/Map/Items/Bomb.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"

game::Bomb::Bomb(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const ModelSoundInfos& modelInfos, const utils::Vector& position, APlayer& player) :
    coordinator(coordinator), entity(coordinator.createEntity()), range(player.getBombRange()), player(player), sound(modelInfos.sound)
{
    static BombId lastId = 0;

    this->id = lastId++;
    this->coordinator.setComponent(this->entity, ecs::component::Attributes{.position = position});
    this->coordinator.setComponent(this->entity, std::move(ecs::component::RenderableObject3d(modelInfos.model.modelPath, modelInfos.model.texturePath)));
    this->coordinator.setComponent(this->entity, std::move(ecs::component::Animation(modelInfos.model.animationPath, 1, modelInfos.model.animationFps)));
    this->coordinator.setComponent(this->entity, ecs::component::Bounds3d{});
    collisionSystem.setEntityNotMoving(this->entity);
    coordinator.getComponent<ecs::component::Animation>(this->entity).addAnimation(1);
}

game::Bomb::Bomb(Bomb&& other) noexcept :
    coordinator(other.coordinator), entity(other.entity), player(other.player), range(other.range), id(other.id), sound(std::move(other.sound)), valid(other.valid)
{
    other.valid = false;
}

game::Bomb::~Bomb()
{
    if (this->valid) {
        this->player.restoreBomb();
        this->coordinator.destroyEntity(this->entity);
    }
}

bool game::Bomb::shouldExplose() const noexcept
{
    if (this->exploded) {
        return true;
    }
    return (this->coordinator.getComponent<ecs::component::Animation>(this->entity).isEnded());
}

unsigned int game::Bomb::getRange() const noexcept
{
    return this->range;
}

game::BombId game::Bomb::getId() const noexcept
{
    return this->id;
}

void game::Bomb::explose() noexcept
{
    if (not this->exploded) {
        audio::AudioPlayer::playSound(this->sound);
        this->exploded = true;
    }
}

utils::Vector game::Bomb::getPosition() const noexcept
{
    return this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
}
