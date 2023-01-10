/*
** EPITECH PROJECT, 2022
** src
** File description:
** LifePowerUp
*/

#include "Game/Map/PowerUp/LifePowerUp.hpp"

game::LifePowerUp::LifePowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept :
    APowerUp(coordinator, modelInfos, position)
{
}

void game::LifePowerUp::doChangesOnPlayer(APlayer& player) noexcept
{
    this->playSound();
    player.addLife();
}
