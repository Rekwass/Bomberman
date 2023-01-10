/*
** EPITECH PROJECT, 2022
** include
** File description:
** PlayersManager
*/

#pragma once

#include "ECS/Core/Events.hpp"
#include "raylib.h"

#include <array>
#include <cstdint>
#include <string>

namespace game {

using PlayerId = int;

struct PlayerKeys {
    int moveUp = KEY_W;
    int moveDown = KEY_S;
    int moveLeft = KEY_A;
    int moveRight = KEY_D;
    int putBomb = KEY_SPACE;
};

enum class PlayerType {
    KEYBOARD,
    AI,
    NETWORK,
};

/*
 * Manage players information
 */
class PlayersManager {
   public:
    PlayersManager() noexcept = delete;
    PlayersManager(PlayersManager const& other) noexcept = delete;
    PlayersManager(PlayersManager&& other) noexcept = delete;
    ~PlayersManager() noexcept = delete;

    PlayersManager& operator=(PlayersManager const& other) noexcept = delete;
    PlayersManager& operator=(PlayersManager&& other) noexcept = delete;

    /*
     * Set the type of player
     *
     * No return value
     *
     * id -> The id of the player (between 1 and 4)
     *
     * type -> The type of the player
     */
    static void setPlayerType(PlayerId id, PlayerType type) noexcept;
    /*
     * Set the keys of a player for local players
     *
     * No return value
     *
     * id -> The id of the player (between 1 and 4)
     *
     * keys -> The key binds of the player
     */
    static void setPlayerKeys(PlayerId id, PlayerKeys keys) noexcept;
    /*
     * Set the texture of a player
     *
     * No return value
     *
     * id -> The id of the player (between 1 and 4)
     *
     * texture -> The texture path
     */
    static void setPlayerTexture(PlayerId id, const std::string& texture) noexcept;
    /*
     * Get the player type
     *
     * Return the player type associated with the given id
     *
     * id -> The player id
     */
    static PlayerType& getPlayerType(PlayerId id) noexcept;
    /*
     * Get the player keybinds
     *
     * Return the player keybinds associated with the given id
     *
     * id -> The player id
     */
    static PlayerKeys& getPlayerKeys(PlayerId id) noexcept;
    /*
     * Get the player texture
     *
     * Return the player texture as a string_view
     *
     * id -> The player id
     */
    static std::string_view getPlayerTexture(PlayerId id) noexcept;

   private:
    static std::array<PlayerType, 4> types;
    static std::array<PlayerKeys, 4> keybinds;
    static std::array<std::string, 4> texturesPath;
};

} // namespace game
