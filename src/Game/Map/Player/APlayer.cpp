/*
** EPITECH PROJECT, 2022
** src
** File description:
** APlayer
*/

#include "Game/Map/Player/APlayer.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "Game/Map/Map.hpp"
#include "Redirect.hpp"
#include "Utils.hpp"

#include <cmath>

game::APlayer::APlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, std::string_view texturePath, const utils::Vector& position, const PlayerId& id, const PlayerType& type) noexcept :
    coordinator(coordinator), entity(coordinator.createEntity()), speed(playersInfos.speed), id(id), type(type), sounds(playersInfos.sounds)
{
    coordinator.setComponent(this->entity, ecs::component::Attributes{.position = position});
    coordinator.setComponent(this->entity, ecs::component::Transform{});
    coordinator.setComponent(this->entity, ecs::component::Bounds3d{});
    coordinator.setComponent(this->entity, std::move(ecs::component::RenderableObject3d(playersInfos.model.modelPath, texturePath)));
    coordinator.setComponent(this->entity, std::move(ecs::component::Animation(playersInfos.model.animationPath, 8, playersInfos.model.animationFps)));

    auto& animation = coordinator.getComponent<ecs::component::Animation>(this->entity);
    animation.addAnimation(1);
    animation.loop(1);
}

game::APlayer::APlayer(APlayer&& other) noexcept :
    coordinator(other.coordinator), entity(other.entity), id(other.id), type(other.type), valid(other.valid)
{
    other.valid = false;
    this->alive = other.alive;
    this->movementNumber = other.movementNumber;
    this->lifes = other.lifes;
    this->bombsNumber = other.bombsNumber;
    this->bombRange = other.bombRange;
}

game::APlayer::~APlayer()
{
    if (this->valid) {
        this->coordinator.destroyEntity(this->entity);
    }
}

static float calculateAngle(utils::Vector point, float lastAngle) noexcept
{
    if (point.x == 0 and point.z == 0) {
        return lastAngle;
    }

    if (point.x == 0 and point.z > 0) {
        return 90;
    } else if (point.x == 0 and point.z < 0) {
        return 270;
    }

    static const double pi = std::acos(-1);
    float angle = std::atan(std::abs(point.z) / std::abs(point.x)) * (180 / pi);

    if (point.x >= 0 and point.z >= 0) {
        return (180 - angle);
    } else if (point.x <= 0 and point.z >= 0) {
        return (angle);
    } else if (point.x <= 0 and point.z <= 0) {
        return (angle - 90);
    } else if (point.x >= 0 and point.z <= 0) {
        return (angle + 180);
    }
    return angle;
}

static float getNewRotationAngle(utils::Vector point, float lastAngle) noexcept
{
    float lastAngleBorder = utils::getInsideBorder(lastAngle);
    auto angle = calculateAngle(point, lastAngleBorder);

    if (lastAngleBorder > angle and lastAngleBorder - angle > 180) {
        angle += 360;
    } else if (angle > lastAngleBorder and angle - lastAngleBorder > 180) {
        angle -= 360;
    }
    return angle;
}

void game::APlayer::moveUp(bool moving)
{
    if (moving) {
        if (not this->movements.up) {
            if (this->movementNumber == 0) {
                startWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movementNumber++;
            this->movements.up = true;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x += this->speed;
        }
    } else {
        if (this->movements.up) {
            this->movementNumber--;
            if (this->movementNumber == 0) {
                stopWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movements.up = false;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x -= this->speed;
        }
    }
    this->setNewRotation();
}

void game::APlayer::moveDown(bool moving)
{
    if (moving) {
        if (not this->movements.down) {
            if (this->movementNumber == 0) {
                startWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movementNumber++;
            this->movements.down = true;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x -= this->speed;
        }
    } else {
        if (this->movements.down) {
            this->movementNumber--;
            if (this->movementNumber == 0) {
                stopWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movements.down = false;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x += this->speed;
        }
    }
    this->setNewRotation();
}

void game::APlayer::moveLeft(bool moving)
{
    if (moving) {
        if (not this->movements.left) {
            if (this->movementNumber == 0) {
                startWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movementNumber++;
            this->movements.left = true;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z -= this->speed;
        }
    } else {
        if (this->movements.left) {
            this->movementNumber--;
            if (this->movementNumber == 0) {
                stopWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movements.left = false;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z += this->speed;
        }
    }
    this->setNewRotation();
}

void game::APlayer::moveRight(bool moving)
{
    if (moving) {
        if (not this->movements.right) {
            if (this->movementNumber == 0) {
                startWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movementNumber++;
            this->movements.right = true;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z += this->speed;
        }
    } else {
        if (this->movements.right) {
            this->movementNumber--;
            if (this->movementNumber == 0) {
                stopWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
            }
            this->movements.right = false;
            this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z -= this->speed;
        }
    }
    this->setNewRotation();
}

void game::APlayer::setNewRotation() noexcept
{
    auto& attributes = this->coordinator.getComponent<ecs::component::Attributes>(this->entity);
    auto& transform = this->coordinator.getComponent<ecs::component::Transform>(this->entity);

    attributes.rotationAxis = {0, 1, 0};
    transform.rotationSpeed = 440;
    transform.rotationAngleGoal = getNewRotationAngle(transform.movement, attributes.rotationAngle);
    attributes.rotationAngle = utils::getInsideBorder(attributes.rotationAngle);
}

void game::APlayer::stop() noexcept
{
    this->moveUp(false);
    this->moveDown(false);
    this->moveLeft(false);
    this->moveRight(false);
}

void game::APlayer::startWalkingAnimation(ecs::component::Animation& animation)
{
    animation.clear();
    animation.addAnimation(2);
    animation.addAnimation(3);
    animation.loop(3);
}

void game::APlayer::stopWalkingAnimation(ecs::component::Animation& animation)
{
    animation.clear();
    animation.addAnimation(1);
    animation.loop(1);
}

unsigned int game::APlayer::getBombRange() const noexcept
{
    return this->bombRange;
}

unsigned int game::APlayer::getLifes() const noexcept
{
    return this->lifes;
}

void game::APlayer::restoreBomb() noexcept
{
    this->bombsNumber++;
}

unsigned int game::APlayer::getLeftBombs() const noexcept
{
    return this->bombsNumber;
}

bool game::APlayer::tryPutBomb(Map& map, utils::Vector position) noexcept
{
    if (this->isTakingDamage() or this->getLeftBombs() <= 0) {
        audio::AudioPlayer::playSound(this->sounds.noBombSound);
        return false;
    }
    return map.putBomb(position, *this);
}

void game::APlayer::useBomb() noexcept
{
    audio::AudioPlayer::playSound(this->sounds.dropBombSound);
    this->bombsNumber--;
}

void game::APlayer::takeDamage()
{
    if (this->isTakingDamage()) {
        return;
    }

    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->entity);

    animation.clear(false, false);
    animation.addAnimation(6, false);
    this->lifes--;
    if (this->lifes < 1) {
        this->die();
    } else {
        audio::AudioPlayer::playSound(this->sounds.damageSound);
    }
}

void game::APlayer::die()
{
    this->alive = false;

    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->entity);

    animation.clear(false, false);
    animation.clear();
    animation.addAnimation(4, false);
    animation.addAnimation(5, false);
    animation.loop(5, false);

    this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement = {0, 0, 0};

    audio::AudioPlayer::playSound(this->sounds.deathSound);
}

utils::Vector game::APlayer::getPosition() const noexcept
{
    return this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
}

bool game::APlayer::isTakingDamage() const noexcept
{
    return (not this->coordinator.getComponent<ecs::component::Animation>(this->entity).isEnded(false));
}

bool game::APlayer::isAlive() const noexcept
{
    return this->alive;
}

void game::APlayer::addLife() noexcept
{
    if (this->lifes < 2) {
        this->lifes++;
    }
}

void game::APlayer::addBombRange() noexcept
{
    this->bombRange++;
}

void game::APlayer::addBomb() noexcept
{
    this->bombsNumber++;
}

void game::APlayer::upgradeSpeed() noexcept
{
    if (this->speedBoosted) {
        return;
    }
    float speedBoost = 0.5;
    if (this->movements.up) {
        this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x += this->speed * speedBoost;
    }
    if (this->movements.down) {
        this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.x -= this->speed * speedBoost;
    }
    if (this->movements.left) {
        this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z -= this->speed * speedBoost;
    }
    if (this->movements.right) {
        this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement.z += this->speed * speedBoost;
    }
    this->speed *= 1 + speedBoost;
    this->speedBoosted = true;
}

void game::APlayer::setPosition(const utils::Vector& position) noexcept
{
    this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position = position;
    this->coordinator.getComponent<ecs::component::Transform>(this->entity).movement = {0, 0, 0};
}

void game::APlayer::setRotation(float rotation) noexcept
{
    auto& attributes = this->coordinator.getComponent<ecs::component::Attributes>(this->entity);

    attributes.rotationAxis = {0, 1, 0};
    attributes.rotationAngle = rotation;
    this->coordinator.getComponent<ecs::component::Transform>(this->entity).rotationAngleGoal = rotation;
}

void game::APlayer::playCelebration()
{
    auto& animation = this->coordinator.getComponent<ecs::component::Animation>(this->entity);

    animation.clear(false, false);
    if (this->alive) {
        animation.addAnimation(7, false);
        animation.loop(7, true, false);
    } else {
        animation.addAnimation(8, false);
        animation.loop(8, true, false);
    }
}

const game::PlayerId& game::APlayer::getId() const noexcept
{
    return this->id;
}

const game::PlayerType& game::APlayer::getType() const noexcept
{
    return this->type;
}
