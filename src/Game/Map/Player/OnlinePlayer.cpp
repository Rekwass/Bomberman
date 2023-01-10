/*
** EPITECH PROJECT, 2022
** src
** File description:
** OnlinePlayer
*/

#include "Game/Map/Player/OnlinePlayer.hpp"

#include "Clock.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "Game/Map/Items/Wall.hpp"
#include "Network/Client.hpp"
#include "Randomizer.hpp"

#include <iostream>

game::OnlinePlayer::OnlinePlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, const utils::Vector& position, const PlayerId& id, Map& map) noexcept :
    APlayer(coordinator, playersInfos, game::PlayersManager::getPlayerTexture(id), position, id, PlayerType::AI), map(map)
{
}

void game::OnlinePlayer::update()
{
    if (this->alive) {
        auto attr = network::Client::getPlayerAttributes(this->id);
        if (not attr.moving and this->moving) {
            this->moving = false;
            stopWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
        } else if (attr.moving and not this->moving) {
            this->moving = true;
            startWalkingAnimation(this->coordinator.getComponent<ecs::component::Animation>(this->entity));
        }
        this->coordinator.getComponent<ecs::component::Attributes>(this->entity) = attr.attr;
    }
}
