/*
** EPITECH PROJECT, 2022
** include
** File description:
** Client
*/

#pragma once

#include "ECS/Components/Attributes.hpp"
#include "Game/PlayersManager.hpp"
#include "Network/ProtectedVar.hpp"

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>

namespace network {

struct PlayersAttributes {
    ecs::component::Attributes attr;
    bool moving{};
};

/*
 * Client Side server connection for online games
 */
class Client {
   public:
    Client() noexcept = delete;
    Client(Client const& other) noexcept = delete;
    Client(Client&& other) noexcept = delete;
    ~Client() noexcept;

    Client& operator=(Client const& other) noexcept = delete;
    Client& operator=(Client&& other) noexcept = delete;

    /*
     * Try to connect to the server on the given ip
     *
     * No return value
     *
     * ip -> The server ip to connect to
     */
    static void tryConnecting(std::string_view ip) noexcept;
    /*
     * Check if the client is connected
     *
     * Return true if the client is connected and false otherwise
     */
    static bool isConnected() noexcept;
    /*
     * Check if the client failed to connect to the last requested server
     *
     * Return true if the client failed to connect to the last requested server and false otherwise
     */
    static bool failedToConnect() noexcept;
    /*
     * Get the id that represent the client on the server
     *
     * Return the id
     */
    static game::PlayerId getId() noexcept;
    /*
     * Get the config content from the server
     *
     * Return the config content as a string
     */
    static std::string getConfig() noexcept;
    /*
     * Set the network client in state InGame
     *
     * No return value
     */
    static void setInGame() noexcept;
    /*
     * Set the network client in state Lobby
     *
     * No return value
     */
    static void setInLobby() noexcept;
    /*
     * Check if the player with the given id is present
     *
     * Return true if the player with the given id is present
     *
     * id -> The player id to get presence for
     */
    static bool isPlayerPresent(game::PlayerId id) noexcept;
    /*
     * Check if the player with the given id is present
     *
     * Return true if the player with the given id is present
     *
     * id -> The player id to get ready state for
     */
    static bool isPlayerReady(game::PlayerId id) noexcept;
    /*
     * Get the texture used by the player
     *
     * Return the texture filepath
     *
     * id -> The player id to get texture for
     */
    static std::string getPlayerTexture(game::PlayerId id) noexcept;
    /*
     * Set the player ready on the server
     *
     * No return value
     *
     * state -> Set to true if the player should be set ready and false otherwise
     */
    static void setReady(bool state = true) noexcept;
    /*
     * Set the player texture on the server
     *
     * No return value
     *
     * texture -> The texture filepath
     */
    static void setTexture(std::string texture) noexcept;
    /*
     * Get the attibutes of the given player
     *
     * Return the attributes of the player
     *
     * id -> The id of the player
     */
    static PlayersAttributes getPlayerAttributes(game::PlayerId id) noexcept;
    /*
     * Set the attributes of the given player
     *
     * No return value
     *
     * id -> The id of the player
     *
     * attributes -> The player attributes
     */
    static void setPlayerAttributes(game::PlayerId id, PlayersAttributes attributes) noexcept;

    /*
     * Pack and unpack type for sending data
     */
    template <typename T>
    class IPacker {
       public:
        IPacker() noexcept = default;
        IPacker(IPacker const& other) noexcept = default;
        IPacker(IPacker&& other) noexcept = default;
        virtual ~IPacker() noexcept = default;

        IPacker& operator=(IPacker const& other) noexcept = default;
        IPacker& operator=(IPacker&& other) noexcept = default;

        /*
         * Pack an object into a string
         *
         * Return the object as a string
         *
         * obj -> The object to pack
         */
        virtual std::string pack(const T& obj) = 0;
        /*
         * Unpack an object from a string
         *
         * The unpacked object
         *
         * str -> The string to unpack
         */
        virtual T unpack(const std::string& str) = 0;
    };
    struct PlayerInfos {
        bool present = false;
        bool ready = false;
        std::string texture;
    };

   private:
    static constexpr int HEADER_SIZE = 64;
    static constexpr int PORT = 28765;
    template <typename T>
    using Type = std::remove_cvref_t<T>;
    enum class GameState {
        WAITING,
        GAME,
    };
    enum class ConnectionState {
        CONNECTING,
        FAILED,
        SUCCESS,
    };

    explicit Client(std::string ip) noexcept;
    /*
     * Loop launched by the thread that watch for updating the server
     *
     * No return value
     *
     * ip -> The ip address of the server
     */
    void loopListener(std::string ip) noexcept;
    /*
     * Send a value with the given header
     *
     * No return value
     *
     * header -> The header of the value
     *
     * data -> The data to pass to the server
     */
    template <typename T, typename TSerializer = void>
    void sendData(const std::string& header, T data) const noexcept
    {
        if constexpr (std::is_same_v<Type<T>, std::string>) {
            sendData(header, data);
        } else {
            TSerializer serializer;
            sendData(header, serializer.pack(data));
        }
    }
    /*
     * Send a data to the server
     *
     * No return value
     *
     * header -> The header of the value
     *
     * value -> The value to send
     */
    void sendData(const std::string& header, const std::string& value) const noexcept;
    /*
     * Send an str to the server
     *
     * No return value
     *
     * str -> The string to send to the server
     */
    void sendStr(const std::string& str) const noexcept;
    /*
     * Read a data from the server
     *
     * No return value
     *
     * header -> The header to identify the value we get
     *
     * id -> The player id to get infos for
     *
     * timeout -> Set to true if the read should be timeouted
     */
    template <typename T = std::string, typename TSerializer = void>
    std::optional<T> read(game::PlayerId id, const std::string& header, bool timeout = true) const noexcept
    {
        if constexpr (std::is_same_v<Type<T>, std::string>) {
            return readStr(id, header, timeout);
        } else {
            TSerializer serializer;

            std::optional<std::string> value = readStr(id, header, timeout);
            if (value.has_value()) {
                return serializer.unpack(value.value());
            }
            return std::nullopt;
        }
    }
    /*
     * Read a data as a astring from the server
     *
     * Return the data as a string
     *
     * id -> The id of the player to get infos for
     *
     * header -> The header to get value associated with
     *
     * timeout -> Set to true if the read should be timeouted
     */
    std::optional<std::string> readStr(game::PlayerId id, const std::string& header, bool timeout) const noexcept;
    /*
     * Receive a str from the socket
     *
     * Return the data as a string
     */
    std::string receiveStr() const noexcept;
    /*
     * Read something in the socket of the given size
     *
     * Return the readed thing as a string
     *
     * size -> The size to read
     */
    std::string readOfSize(int size) const noexcept;

    static std::unique_ptr<Client> instance;
    std::thread thread;
    int sock = 0;
    ProtectedVar<bool> active{true};
    ProtectedVar<game::PlayerId> id{};
    ProtectedVar<std::string> config{};
    ProtectedVar<GameState> gameState{};
    ProtectedVar<ConnectionState> connection{};
    std::array<ProtectedVar<PlayersAttributes>, 4> playersAttributes;
    std::array<ProtectedVar<PlayerInfos>, 4> playersInfos;
};

} // namespace network
