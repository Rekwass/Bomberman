/*
** EPITECH PROJECT, 2022
** include
** File description:
** Packers
*/

#pragma once

#include "Network/Client.hpp"

#include <string>

namespace network {

/*
 * Data packer and unpacker for player informations
 */
class PlayerInfosPacker final : public Client::IPacker<Client::PlayerInfos> {
   public:
    PlayerInfosPacker() noexcept = default;
    PlayerInfosPacker(PlayerInfosPacker const& other) noexcept = default;
    PlayerInfosPacker(PlayerInfosPacker&& other) noexcept = default;
    ~PlayerInfosPacker() noexcept final = default;

    PlayerInfosPacker& operator=(PlayerInfosPacker const& other) noexcept = default;
    PlayerInfosPacker& operator=(PlayerInfosPacker&& other) noexcept = default;

    /*
     * Pack an object into a string
     *
     * Return the object as a string
     *
     * obj -> The object to pack
     */
    std::string pack(const Client::PlayerInfos& obj) final;
    /*
     * Unpack an object from a string
     *
     * The unpacked object
     *
     * str -> The string to unpack
     */
    Client::PlayerInfos unpack(const std::string& str) final;
};

/*
 * Data packer and unpacker for player attributes
 */
class PlayerAttributesPacker final : public Client::IPacker<PlayersAttributes> {
   public:
    PlayerAttributesPacker() noexcept = default;
    PlayerAttributesPacker(PlayerAttributesPacker const& other) noexcept = default;
    PlayerAttributesPacker(PlayerAttributesPacker&& other) noexcept = default;
    ~PlayerAttributesPacker() noexcept final = default;

    PlayerAttributesPacker& operator=(PlayerAttributesPacker const& other) noexcept = default;
    PlayerAttributesPacker& operator=(PlayerAttributesPacker&& other) noexcept = default;

    /*
     * Pack an object into a string
     *
     * Return the object as a string
     *
     * obj -> The object to pack
     */
    std::string pack(const PlayersAttributes& obj) final;
    /*
     * Unpack an object from a string
     *
     * The unpacked object
     *
     * str -> The string to unpack
     */
    PlayersAttributes unpack(const std::string& str) final;
};

} // namespace network
