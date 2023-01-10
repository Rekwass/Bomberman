/*
** EPITECH PROJECT, 2022
** src
** File description:
** SpeedPowerUp
*/

#include "Game/Map/PowerUp/SpeedPowerUp.hpp"

game::SpeedPowerUp::SpeedPowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept :
    APowerUp(coordinator, modelInfos, position) { }

void game::SpeedPowerUp::doChangesOnPlayer(APlayer& player) noexcept
{
    this->playSound();
    player.upgradeSpeed();
}
