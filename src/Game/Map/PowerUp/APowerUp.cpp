/*
** EPITECH PROJECT, 2022
** src
** File description:
** APowerUp
*/

#include "Game/Map/PowerUp/APowerUp.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/RenderableObject3d.hpp"

game::APowerUp::APowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& powerUpInfos, const utils::Vector& position) noexcept :
    coordinator(coordinator), entity(coordinator.createEntity()), sound(powerUpInfos.sound)
{
    coordinator.setComponent(this->entity, ecs::component::Attributes{.position = position});
    coordinator.setComponent(this->entity, ecs::component::RenderableObject3d(powerUpInfos.model.modelPath, powerUpInfos.model.texturePath));
    coordinator.setComponent(this->entity, ecs::component::Animation(powerUpInfos.model.animationPath, 1, powerUpInfos.model.animationFps));

    auto& animation = coordinator.getComponent<ecs::component::Animation>(this->entity);
    animation.addAnimation(1);
    animation.loop(1);
}

game::APowerUp::APowerUp(APowerUp&& other) noexcept :
    coordinator(other.coordinator), entity(other.entity), sound(std::move(other.sound)), valid(other.valid)
{
    other.valid = false;
    this->used = other.used;
}

game::APowerUp::~APowerUp()
{
    if (this->valid) {
        this->coordinator.destroyEntity(this->entity);
    }
}

void game::APowerUp::apply(APlayer& player) noexcept
{
    if (not this->used) {
        this->used = true;
        this->doChangesOnPlayer(player);
    }
}

utils::Vector game::APowerUp::getPosition() const noexcept
{
    return this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
}

void game::APowerUp::playSound() const noexcept
{
    audio::AudioPlayer::playSound(this->sound);
}
