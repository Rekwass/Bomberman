/*
** EPITECH PROJECT, 2022
** src
** File description:
** Packers
*/

#include "Network/Packers.hpp"

#include "fmt/core.h"

#include <sstream>

static constexpr char separator = '@';

std::string network::PlayerInfosPacker::pack(const Client::PlayerInfos& obj)
{
    return fmt::format("{}{}{}{}{}", (obj.present ? "1" : "0"), separator, (obj.ready ? "1" : "0"), separator, obj.texture);
}

network::Client::PlayerInfos network::PlayerInfosPacker::unpack(const std::string& str)
{
    if (str.empty()) {
        return {.present = false, .ready = false, .texture = ""};
    }

    Client::PlayerInfos infos;
    std::string part;
    std::istringstream s(str);

    std::getline(s, part, separator);
    infos.present = (part.front() == '1');

    std::getline(s, part, separator);
    infos.ready = (part.front() == '1');

    std::getline(s, part, separator);
    infos.texture = part;

    return infos;
}

std::string network::PlayerAttributesPacker::pack(const PlayersAttributes& obj)
{
    return fmt::format("{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}", (obj.moving ? "1" : "0"), separator, obj.attr.position.x, separator, obj.attr.position.y, separator, obj.attr.position.z, separator, obj.attr.rotationAngle, separator, obj.attr.rotationAxis.x, separator, obj.attr.rotationAxis.y, separator, obj.attr.rotationAxis.z, separator, obj.attr.scale);
}

network::PlayersAttributes network::PlayerAttributesPacker::unpack(const std::string& str)
{
    if (str.empty()) {
        return {};
    }

    PlayersAttributes attr;
    std::string part;
    std::istringstream s(str);

    std::getline(s, part, separator);
    attr.moving = (part.front() == '1');

    std::getline(s, part, separator);
    attr.attr.position.x = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.position.y = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.position.z = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.rotationAngle = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.rotationAxis.x = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.rotationAxis.y = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.rotationAxis.z = std::stof(part);

    std::getline(s, part, separator);
    attr.attr.scale = std::stof(part);

    return attr;
}
