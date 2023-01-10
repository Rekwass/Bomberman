/*
** EPITECH PROJECT, 2022
** src
** File description:
** BombNumberPowerUp
*/

#include "Game/Map/PowerUp/BombNumberPowerUp.hpp"

game::BombNumberPowerUp::BombNumberPowerUp(ecs::Coordinator& coordinator, const ModelSoundInfos& modelInfos, const utils::Vector& position) noexcept :
    APowerUp(coordinator, modelInfos, position) { }

void game::BombNumberPowerUp::doChangesOnPlayer(APlayer& player) noexcept
{
    this->playSound();
    player.addBomb();
}
