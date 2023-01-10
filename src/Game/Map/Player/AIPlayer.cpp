/*
** EPITECH PROJECT, 2022
** src
** File description:
** AIPlayer
*/

#include "Game/Map/Player/AIPlayer.hpp"

#include "Clock.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "Game/Map/Items/Wall.hpp"
#include "Network/Client.hpp"
#include "Randomizer.hpp"

game::AIPlayer::AIPlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, const utils::Vector& position, const PlayerId& id, Map& map) noexcept :
    APlayer(coordinator, playersInfos, playersInfos.model.texturePath, position, id, PlayerType::AI), map(map)
{
    auto& animation = coordinator.getComponent<ecs::component::Animation>(this->entity);
    auto& attributes = coordinator.getComponent<ecs::component::Attributes>(this->entity);
    auto& transform = coordinator.getComponent<ecs::component::Transform>(this->entity);
}

void game::AIPlayer::addDirection(const AroundMapPartStates& states, std::vector<Direction>& newDirs, PartState partState) const noexcept
{
    if (states.up == partState and this->oldDirection != Direction::DOWN) {
        newDirs.emplace_back(Direction::UP);
    }
    if (states.right == partState and this->oldDirection != Direction::LEFT) {
        newDirs.emplace_back(Direction::RIGHT);
    }
    if (states.down == partState and this->oldDirection != Direction::UP) {
        newDirs.emplace_back(Direction::DOWN);
    }
    if (states.left == partState and this->oldDirection != Direction::RIGHT) {
        newDirs.emplace_back(Direction::LEFT);
    }
}

void game::AIPlayer::addAnyDirection(const AroundMapPartStates& states, std::vector<Direction>& newDirs, PartState partState) noexcept
{
    if (states.up == partState) {
        newDirs.emplace_back(Direction::UP);
    }
    if (states.right == partState) {
        newDirs.emplace_back(Direction::RIGHT);
    }
    if (states.down == partState) {
        newDirs.emplace_back(Direction::DOWN);
    }
    if (states.left == partState) {
        newDirs.emplace_back(Direction::LEFT);
    }
}

void game::AIPlayer::addStandStill(const AroundMapPartStates& states, std::vector<Direction>& newDirs) noexcept
{
    if (states.middle == PartState::FREE) {
        newDirs.emplace_back(Direction::MIDDLE);
    }
}

game::PartState game::AIPlayer::getPartStateFromDirection(Direction dir, const AroundMapPartStates& states) noexcept
{
    if (dir == Direction::UP) {
        return states.up;
    } else if (dir == Direction::RIGHT) {
        return states.right;
    } else if (dir == Direction::DOWN) {
        return states.down;
    } else if (dir == Direction::LEFT) {
        return states.left;
    }
    return states.middle;
}

void game::AIPlayer::placeBomb(const std::vector<Direction>& newDirs, const AroundMapPartStates& around, const AroundMapPartTypes& aroundType) noexcept
{
    if (newDirs.size() == 1 and getPartStateFromDirection(newDirs.at(0), around) == PartState::FREE and newDirs.at(0) != Direction::MIDDLE and around.middle == PartState::FREE and this->bombsNumber != 0) {
        if ((around.up != PartState::FIRE and around.right != PartState::FIRE and around.down != PartState::FIRE and around.left != PartState::FIRE) and (aroundType.up == PartType::BOX or aroundType.right == PartType::BOX or aroundType.down == PartType::BOX or aroundType.left == PartType::BOX)) {
            this->tryPutBomb(this->map, this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position);
        }
    }
}

void game::AIPlayer::recenterAI(utils::Vector& position) const noexcept
{
    auto newPos = this->map.getNearestPartCenter(position);

    position = newPos;
}

void game::AIPlayer::update()
{
    if (this->alive) {
        if (this->clock.isElapsed(100)) {
            this->clock.saveTimePoint();
            std::vector<Direction> newDirs = {};

            auto& position = this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
            auto bounds = GetModelBoundingBox(this->coordinator.getComponent<ecs::component::RenderableObject3d>(this->entity).getModel());
            bounds.min.x += position.x;
            bounds.min.y += position.y;
            bounds.min.z += position.z;
            bounds.max.x += position.x;
            bounds.max.y += position.y;
            bounds.max.z += position.z;
            AroundMapPartStates around = this->map.getAroundParts(position);
            AroundMapPartTypes aroundType = this->map.getAroundPartsType(position);

            this->addAnyDirection(around, newDirs, PartState::POWER_UP);
            if (newDirs.empty()) {
                this->addDirection(around, newDirs, PartState::FREE);
            }
            if (newDirs.empty()) {
                this->addAnyDirection(around, newDirs, PartState::FREE);
            }
            if (newDirs.empty()) {
                addStandStill(around, newDirs);
            }
            if (newDirs.empty()) {
                this->addDirection(around, newDirs, PartState::DANGER);
            }
            if (newDirs.empty()) {
                this->addAnyDirection(around, newDirs, PartState::DANGER);
            }
            if (newDirs.empty()) {
                this->addDirection(around, newDirs, PartState::FIRE);
            }
            if (newDirs.empty()) {
                this->addAnyDirection(around, newDirs, PartState::FIRE);
            }
            if (newDirs.empty()) {
                newDirs.emplace_back(Direction::MIDDLE);
            }

            Direction newDir = newDirs.at(utils::Randomizer::getRandomNumber<int>(0, newDirs.size() - 1));

            if (not this->map.isCompletelyInsidePart(position, bounds, 1) and this->oldPosition != position) {
                newDir = this->oldDirection;
            }

            if (this->oldDirection == newDir and this->oldPosition != position) {
                this->oldPosition = this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
                return;
            }
            if (this->oldPosition == position and newDir != Direction::MIDDLE) {
                recenterAI(position);
            }

            if (this->oldDirection == Direction::UP) {
                this->moveUp(false);
            } else if (this->oldDirection == Direction::DOWN) {
                this->moveDown(false);
            } else if (this->oldDirection == Direction::LEFT) {
                this->moveLeft(false);
            } else if (this->oldDirection == Direction::RIGHT) {
                this->moveRight(false);
            }

            if (newDir == Direction::UP) {
                this->moveUp();
            } else if (newDir == Direction::DOWN) {
                this->moveDown();
            } else if (newDir == Direction::LEFT) {
                this->moveLeft();
            } else if (newDir == Direction::RIGHT) {
                this->moveRight();
            }

            placeBomb(newDirs, around, aroundType);
            this->oldDirection = newDir;
            this->oldPosition = this->coordinator.getComponent<ecs::component::Attributes>(this->entity).position;
        }
    }
    network::Client::setPlayerAttributes(this->id, {this->coordinator.getComponent<ecs::component::Attributes>(this->entity), this->movementNumber > 0});
}
