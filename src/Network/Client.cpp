/*
** EPITECH PROJECT, 2022
** src
** File description:
** Client
*/

#include "Network/Client.hpp"

#include "Network/Packers.hpp"
#include "Network/Socket.hpp"
#include "fmt/core.h"

#include <iostream>

std::unique_ptr<network::Client> network::Client::instance = nullptr;

network::Client::Client(std::string ip) noexcept :
    thread(&network::Client::loopListener, &(*this), std::move(ip))
{
    this->connection.write(ConnectionState::CONNECTING);
}

network::Client::~Client() noexcept
{
    this->active.write(false);
    this->thread.join();
}

// NOLINTNEXTLINE
void network::Client::loopListener(std::string ip) noexcept
{
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
    // NOLINTNEXTLINE
    fcntl(this->sock, F_SETFL, O_NONBLOCK);

#if defined(windows)
    WSADATA WsaData;
    WSAStartup(MAKEWORD(2, 0), &this->WsaData);
#elif defined(linux)
    sockaddr_in server{
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr = {.s_addr = inet_addr(ip.c_str())}};
#endif

    // NOLINTNEXTLINE
    connect(this->sock, (reinterpret_cast<sockaddr*>(&server)), sizeof(server));
    {
        fd_set fdset;
        timeval tv = {5, 0};
        // NOLINTNEXTLINE
        FD_ZERO(&fdset);
        // NOLINTNEXTLINE
        FD_SET(this->sock, &fdset);

        if (select(this->sock + 1, nullptr, &fdset, nullptr, &tv) <= 0) {
            this->connection.write(ConnectionState::FAILED);
            close(this->sock);
            return;
        }
    }
    game::PlayerId id = std::stoi(this->read<std::string>(0, "ID").value());
    if (id < 1 or id > 4) {
        this->connection.write(ConnectionState::FAILED);
        close(this->sock);
        return;
    }
    this->id.write(id);
    this->config.write(this->read<std::string>(0, "CONFIG").value());
    this->playersInfos.at(id - 1).write({.present = true});
    this->connection.write(ConnectionState::SUCCESS);

    while (this->active.read()) {
        switch (this->gameState.read()) {
        case GameState::WAITING:
            for (game::PlayerId id = 1; id < 5; id++) {
                if (id == this->id.read()) {
                    this->sendData<PlayerInfos, PlayerInfosPacker>("PLAYERINFOS", this->playersInfos.at(id - 1).read());
                } else {
                    auto infos = this->read<PlayerInfos, PlayerInfosPacker>(id, "PLAYERINFOS");
                    if (infos.has_value()) {
                        this->playersInfos.at(id - 1).write(infos.value());
                    }
                }
            }
            break;
        case GameState::GAME:
            for (game::PlayerId id = 1; id < 5; id++) {
                if (id == this->id.read()) {
                    this->sendData<PlayersAttributes, PlayerAttributesPacker>("PLAYERATTRIBUTES", this->playersAttributes.at(id - 1).read());
                } else {
                    auto attr = this->read<PlayersAttributes, PlayerAttributesPacker>(id, "PLAYERATTRIBUTES");
                    if (attr.has_value()) {
                        this->playersAttributes.at(id - 1).write(attr.value());
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    close(this->sock);
}

void network::Client::tryConnecting(std::string_view ip) noexcept
{
    instance.reset(new Client(std::string{ip}));
}

bool network::Client::isConnected() noexcept
{
    return (instance->connection.read() == ConnectionState::SUCCESS);
}

bool network::Client::failedToConnect() noexcept
{
    return (instance->connection.read() == ConnectionState::FAILED);
}

game::PlayerId network::Client::getId() noexcept
{
    return (instance->id.read());
}

std::string network::Client::getConfig() noexcept
{
    return (instance->config.read());
}

void network::Client::setInLobby() noexcept
{
    instance->gameState.write(GameState::WAITING);
}

void network::Client::setInGame() noexcept
{
    instance->gameState.write(GameState::GAME);
}

bool network::Client::isPlayerPresent(game::PlayerId id) noexcept
{
    return (instance->playersInfos.at(id - 1).read().present);
}

bool network::Client::isPlayerReady(game::PlayerId id) noexcept
{
    return (instance->playersInfos.at(id - 1).read().ready);
}

std::string network::Client::getPlayerTexture(game::PlayerId id) noexcept
{
    return (instance->playersInfos.at(id - 1).read().texture);
}

void network::Client::setReady(bool state) noexcept
{
    auto infos = instance->playersInfos.at(getId() - 1).read();

    infos.ready = state;
    instance->playersInfos.at(getId() - 1).write(infos);
}

void network::Client::setTexture(std::string texture) noexcept
{
    auto infos = instance->playersInfos.at(getId() - 1).read();

    infos.texture = std::move(texture);
    instance->playersInfos.at(getId() - 1).write(infos);
}

network::PlayersAttributes network::Client::getPlayerAttributes(game::PlayerId id) noexcept
{
    return (instance->playersAttributes.at(id - 1).read());
}

void network::Client::setPlayerAttributes(game::PlayerId id, PlayersAttributes attributes) noexcept
{
    instance->playersAttributes.at(id - 1).write(attributes);
}

void network::Client::sendData(const std::string& header, const std::string& value) const noexcept
{
    this->sendStr(fmt::format("SET|{}|{}", header, value));
}

void network::Client::sendStr(const std::string& str) const noexcept
{
    std::string comHeader = std::to_string(str.length());
    comHeader.resize(HEADER_SIZE, '\0');

    send(this->sock, comHeader.c_str(), comHeader.length(), 0);

    send(this->sock, str.c_str(), str.length(), 0);
}

std::optional<std::string> network::Client::readStr(game::PlayerId id, const std::string& header, bool timeout) const noexcept
{
    this->sendStr(fmt::format("GET|{}|{}", header, id));

    if (timeout) {
        fd_set rfds;
        timeval tv{1, 0};
        // NOLINTNEXTLINE
        FD_ZERO(&rfds);
        // NOLINTNEXTLINE
        FD_SET(this->sock, &rfds);
        if (select(this->sock + 1, &rfds, nullptr, nullptr, &tv) > 0) {
            return this->receiveStr();
        }
        return std::nullopt;
    }
    return this->receiveStr();
}

std::string network::Client::receiveStr() const noexcept
{
    int dataSize = std::stoi(this->readOfSize(HEADER_SIZE));

    return this->readOfSize(dataSize);
}

std::string network::Client::readOfSize(int size) const noexcept
{
    char data[size];
    std::string buffer;
    int sizeBuffer = 0;
    int readedSize = 1;

    while (readedSize > 0 and sizeBuffer < size) {
        fd_set rfds;
        // NOLINTNEXTLINE
        FD_ZERO(&rfds);
        // NOLINTNEXTLINE
        FD_SET(this->sock, &rfds);
        select(this->sock + 1, &rfds, nullptr, nullptr, nullptr);

        readedSize = recv(this->sock, data, size - sizeBuffer, 0);
        data[readedSize] = '\0';
        buffer.append(data);
        sizeBuffer += readedSize;
    }
    return std::move(buffer);
}
