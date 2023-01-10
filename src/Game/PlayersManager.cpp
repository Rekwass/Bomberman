/*
** EPITECH PROJECT, 2022
** src
** File description:
** PlayersManager
*/

#include "Game/PlayersManager.hpp"

std::array<game::PlayerType, 4> game::PlayersManager::types{game::PlayerType::AI, game::PlayerType::AI, game::PlayerType::AI, game::PlayerType::AI};
std::array<game::PlayerKeys, 4> game::PlayersManager::keybinds;
std::array<std::string, 4> game::PlayersManager::texturesPath;

void game::PlayersManager::setPlayerType(PlayerId id, PlayerType type) noexcept
{
    if (id > 0 and id < 5) {
        types.at(id - 1) = type;
    }
}

void game::PlayersManager::setPlayerKeys(PlayerId id, PlayerKeys keys) noexcept
{
    if (id > 0 and id < 5) {
        keybinds.at(id - 1) = keys;
    }
}

void game::PlayersManager::setPlayerTexture(PlayerId id, const std::string& texture) noexcept
{
    if (id > 0 and id < 5) {
        texturesPath.at(id - 1) = texture;
    }
}

game::PlayerType& game::PlayersManager::getPlayerType(PlayerId id) noexcept
{
    return types.at(id - 1);
}

game::PlayerKeys& game::PlayersManager::getPlayerKeys(PlayerId id) noexcept
{
    return keybinds.at(id - 1);
}

std::string_view game::PlayersManager::getPlayerTexture(PlayerId id) noexcept
{
    return texturesPath.at(id - 1);
}
