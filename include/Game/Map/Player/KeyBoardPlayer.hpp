/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** KeyBoardPlayer
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"
#include "Game/Map/ObjectsInfos.hpp"
#include "Game/Map/Player/APlayer.hpp"
#include "Game/PlayersManager.hpp"
#include "Vector.hpp"

namespace game {

class Map;

/*
 * Keyboard managed player
 */
class KeyBoardPlayer final : public APlayer {
   public:
    KeyBoardPlayer() noexcept = delete;
    KeyBoardPlayer(ecs::Coordinator& coordinator, const PlayersInfos& playersInfos, std::string_view texturePath, const utils::Vector& position, const PlayerId& id, const PlayerKeys& playerKeys, Map& map) noexcept;
    KeyBoardPlayer(KeyBoardPlayer const& other) noexcept = delete;
    KeyBoardPlayer(KeyBoardPlayer&& other) noexcept = default;
    ~KeyBoardPlayer() noexcept final = default;

    KeyBoardPlayer& operator=(KeyBoardPlayer const& other) noexcept = delete;
    KeyBoardPlayer& operator=(KeyBoardPlayer&& other) noexcept = delete;

    void update() final;

   private:
    Map& map;
    bool puttingBomb = false;
    Movement movement;
    PlayerKeys playerKeys;
};

} // namespace game
