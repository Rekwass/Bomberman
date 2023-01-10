/*
** EPITECH PROJECT, 2022
** src
** File description:
** BombRangePowerUp
*/

#include "Game/Map/PowerUp/BombRangePowerUp.hpp"

game::BombRangePowerUp::BombRangePowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept :
    APowerUp(coordinator, modelInfos, position) { }

void game::BombRangePowerUp::doChangesOnPlayer(APlayer& player) noexcept
{
    this->playSound();
    player.addBombRange();
}
