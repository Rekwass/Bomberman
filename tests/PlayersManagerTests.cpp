/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** PlayersManagerTests
*/

#include "Game/PlayersManager.hpp"

#include <gtest/gtest-matchers.h>
#include <gtest/gtest.h>

TEST(PlayersManager, setPlayerType)
{
    EXPECT_NO_THROW(game::PlayersManager::setPlayerType(1, game::PlayerType::KEYBOARD));
}

TEST(PlayersManager, setPlayersKeys)
{
    EXPECT_NO_THROW(game::PlayersManager::setPlayerKeys(1, {.moveUp = KEY_W}));
}

TEST(PlayersManager, getPlayerType)
{
    game::PlayerId playerId = 1;
    game::PlayerType playerType = game::PlayerType::KEYBOARD;

    EXPECT_NO_THROW(game::PlayersManager::setPlayerType(playerId, playerType));
    game::PlayerType& res = game::PlayersManager::getPlayerType(playerId);
    EXPECT_EQ(static_cast<int>(res), static_cast<int>(playerType));
}

TEST(PlayersManager, getPlayersKeys)
{
    game::PlayerKeys playerKeys = {.moveUp = KEY_W};
    game::PlayersManager::setPlayerKeys(1, playerKeys);
    game::PlayerKeys& res = game::PlayersManager::getPlayerKeys(1);
    EXPECT_EQ(static_cast<int>(res.moveUp), static_cast<int>(playerKeys.moveUp));
}
