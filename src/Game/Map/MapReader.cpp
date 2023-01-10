/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** MapReader
*/

#include "Game/Map/MapReader.hpp"

#include "FileReader.hpp"
#include "Redirect.hpp"
#include "raylib.h"

#include <cmath>
#include <functional>
#include <iostream>
#include <sys/stat.h>

char game::MapReader::getChar(nlohmann::json element, std::string_view key, std::string_view prefix)
{
    std::string tmp;

    if (not element.contains(key.data())) {
        throw error::MapLoaderError(fmt::format("Cannot find '{}{}' key.", prefix.data(), key.data()));
    }
    if (not element.at(key.data()).is_string()) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is not a string.", prefix.data(), key.data()));
    }
    tmp = element.at(key.data()).get<std::string>();
    if (tmp.empty()) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is empty.", prefix.data(), key.data()));
    } else if (tmp.length() > 1) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is not a char({}).", prefix.data(), key.data(), tmp));
    }
    return tmp.at(0);
}

int game::MapReader::getInt(nlohmann::json element, std::string_view key, std::string_view prefix)
{
    if (not element.contains(key.data())) {
        throw error::MapLoaderError(fmt::format("Cannot find '{}{}' key.", prefix.data(), key.data()));
    }
    if (not element.at(key.data()).is_number()) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is not a number.", prefix.data(), key.data()));
    }
    return element.at(key.data()).get<int>();
}

float game::MapReader::getFloat(nlohmann::json element, std::string_view key, std::string_view prefix)
{
    if (not element.contains(key.data())) {
        throw error::MapLoaderError(fmt::format("Cannot find '{}{}' key.", prefix.data(), key.data()));
    }
    if (not element.at(key.data()).is_number()) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is not a number.", prefix.data(), key.data()));
    }
    return element.at(key.data()).get<float>();
}

game::MapReader::MapReader(std::string file, const utils::Vector& maximumMapSize, bool haveFile)
{
    try {
        nlohmann::json json;

        if (haveFile) {
            if (not game::MapReader::doesExist(file)) {
                throw error::MapLoaderError(fmt::format("Config file ({}) does not exist or is inaccessible", file));
            }
            std::ifstream s(file.data());
            s >> json;
        } else {
            json = nlohmann::json::parse(file);
        }

        this->parseJson(std::move(json), maximumMapSize);
    } catch (const nlohmann::json::exception& e) {
        throw error::MapLoaderError(fmt::format("Failed to parse json config file '{}': {}", file, e.what()));
    }
}

std::string game::MapReader::getString(nlohmann::json element, std::string_view key, std::string_view prefix)
{
    std::string str;

    if (not element.contains(key.data())) {
        throw error::MapLoaderError(fmt::format("Cannot find '{}{}' key.", prefix.data(), key.data()));
    }
    if (not element.at(key.data()).is_string()) {
        throw error::MapLoaderError(fmt::format("'{}{}' value is not a string.", prefix.data(), key.data()));
    }
    str = element.at(key.data()).get<std::string>();
    if (not doesExist(str)) {
        throw error::MapLoaderError(fmt::format("File '{}' not found.", str));
    }
    return str;
}

void game::MapReader::parseJson(nlohmann::json json, const utils::Vector& maximumMapSize)
{
    this->getReferenceSize(json);
    this->readBombs(json);
    this->readPlayers(json);
    this->readPowerUps(json);
    this->parseWalls(json.at("identifiers").at("walls"));
    this->parseGrounds(json.at("identifiers").at("grounds"));
    this->parseBoxes(json.at("identifiers").at("boxes"));
    this->parsePlayers(json.at("identifiers").at("players"));
    this->readMap(json);
    this->checkMapValidity(maximumMapSize);
}

const game::PartInfos& game::MapReader::getInfosFor(char c) const noexcept
{
    return this->parts.at(c);
}

const utils::Vector& game::MapReader::getBlockSize() const noexcept
{
    return this->blockSize;
}

const std::vector<std::vector<char>>& game::MapReader::getMap() const noexcept
{
    return this->map;
}

bool game::MapReader::doesExist(std::string_view filePath) noexcept
{
    struct stat buffer {
    };
    return (stat(filePath.data(), &buffer) == 0);
}

utils::Vector game::MapReader::getSize(std::string modelPath) noexcept
{
    static std::unordered_map<std::string, utils::Vector> buf = {};

    if (buf.contains(modelPath)) {
        return buf.at(modelPath);
    }

    Model model = LoadModel(modelPath.data());

    BoundingBox box = GetModelBoundingBox(model);
    UnloadModel(model);
    utils::Vector vec = {box.max.x - box.min.x, box.max.y - box.min.y, box.max.z - box.min.z};
    buf.insert({modelPath, vec});

    return vec;
}

bool game::MapReader::checkMapValidity(utils::Vector maximumMapSize) const
{
    int playerCount = 0;

    if (this->blockSize.x * this->map.size() > maximumMapSize.x) {
        throw error::MapLoaderError(fmt::format("The height of the map is higher than the maximum one, actual is {} and maximum is {}", this->blockSize.x * this->map.size(), maximumMapSize.x));
    }
    for (const auto& line : this->map) {
        if (this->blockSize.z * line.size() > maximumMapSize.z) {
            throw error::MapLoaderError(fmt::format("The width of the map is higher than the maximum one, actual is {} and maximum is {}", this->blockSize.z * line.size(), maximumMapSize.z));
        }
        for (const auto& c : line) {
            if (not this->parts.contains(c)) {
                throw error::MapLoaderError(fmt::format("Invalid map, the map contain an unrecognized identifier: {}", c));
            }
            if (this->parts.at(c).type == PartType::PLAYER) {
                playerCount++;
            }
        }
    }
    if (playerCount != 4) {
        throw error::MapLoaderError(fmt::format("Invalid map, the map must have 4 players but currently have {}", playerCount));
    }
    return true;
}

float game::MapReader::getXDifference(utils::Vector size1, utils::Vector size2) noexcept
{
    float diffX = 0;

    if (size1.x > size2.x) {
        diffX = -(100 - ((size2.x * 100) / size1.x));
    } else {
        diffX = 100 - ((size1.x * 100) / size2.x);
    }
    return (diffX);
}

float game::MapReader::getZDifference(utils::Vector size1, utils::Vector size2) noexcept
{
    float diffZ = 0;

    if (size1.z > size2.z) {
        diffZ = -(100 - ((size2.z * 100) / size1.z));
    } else {
        diffZ = 100 - ((size1.z * 100) / size2.z);
    }
    return (diffZ);
}

float game::MapReader::getHighestDifference(utils::Vector size1, utils::Vector size2) noexcept
{
    float diffX = getXDifference(size1, size2);
    float diffZ = getZDifference(size1, size2);

    if (std::abs(diffX) > std::abs(diffZ)) {
        return diffX;
    }
    return diffZ;
}

void game::MapReader::parseWalls(nlohmann::json& walls)
{
    char c = 0;
    std::string modelPath;
    std::string groundPath;
    utils::Vector size{};
    float sizeDiff = 0;

    for (const auto& wall : walls) {
        c = getChar(wall, "identifier", "identifiers.walls:");
        modelPath = getString(wall, "model", "identifiers.walls:");
        groundPath = getString(wall, "groundModel", "identifiers.walls:");

        size = getSize(modelPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The wall '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }

        size = getSize(groundPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The ground '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }

        if (this->parts.contains(c)) {
            throw error::MapLoaderError(fmt::format("'{}' is defined multiple times.", c));
        }
        this->parts.insert({c, {groundPath, getString(wall, "groundTexture", "identifiers.walls:"), PartType::WALL, modelPath, getString(wall, "texture", "identifiers.walls:")}});
    }
}

void game::MapReader::parseGrounds(nlohmann::json& grounds)
{
    char c = 0;
    std::string modelPath;
    utils::Vector size{};
    float sizeDiff = 0;

    for (const auto& ground : grounds) {
        c = getChar(ground, "identifier", "identifiers.grounds:");
        modelPath = getString(ground, "model", "identifiers.grounds:");

        size = getSize(modelPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The ground '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }

        if (this->parts.contains(c)) {
            throw error::MapLoaderError(fmt::format("'{}' is defined multiple times.", c));
        }
        this->parts.insert({c, {modelPath, getString(ground, "texture", "identifiers.grounds:"), PartType::GROUND}});
    }
}

void game::MapReader::parseBoxes(nlohmann::json& boxes)
{
    char c = 0;
    std::string modelPath;
    std::string groundPath;
    utils::Vector size{};
    float sizeDiff = 0;

    for (const auto& box : boxes) {
        c = getChar(box, "identifier", "identifiers.boxes:");
        modelPath = getString(box, "model", "identifiers.boxes:");
        groundPath = getString(box, "groundModel", "identifiers.boxes:");

        size = getSize(modelPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The box '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }
        size = getSize(groundPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The ground '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }

        if (this->parts.contains(c)) {
            throw error::MapLoaderError(fmt::format("'{}' is defined multiple times.", c));
        }
        this->parts.insert({c, {groundPath, getString(box, "groundTexture", "identifiers.boxes:"), PartType::BOX, modelPath, getString(box, "texture", "identifiers.boxes:")}});
    }
}

void game::MapReader::parsePlayers(nlohmann::json& players)
{
    char c = 0;
    std::string modelPath;
    utils::Vector size{};
    float sizeDiff = 0;

    for (const auto& player : players) {
        c = getChar(player, "identifier", "identifiers.players:");
        modelPath = getString(player, "groundModel", "identifiers.players:");

        size = getSize(modelPath);
        sizeDiff = getHighestDifference(size, this->blockSize);
        if (std::abs(sizeDiff) > 10) {
            throw error::MapLoaderError(fmt::format("The ground '{}' size should be only ~10% smaller / bigger than the reference size. Current is {}%", modelPath, sizeDiff));
        }

        if (this->parts.contains(c)) {
            throw error::MapLoaderError(fmt::format("'{}' is defined multiple times.", c));
        }
        this->parts.insert({c, {modelPath, getString(player, "groundTexture", "identifiers.players:"), PartType::PLAYER}});
    }
}

void game::MapReader::getReferenceSize(nlohmann::json& json)
{
    this->blockSize = game::MapReader::getSize(getString(json, "referenceModel"));
}

void game::MapReader::readMap(nlohmann::json& json)
{
    auto mapPath = getString(json, "map");

    try {
        std::string strMap = utils::FileReader::GetContentFromFile(mapPath);
        std::istringstream iss(strMap);

        for (std::string line; std::getline(iss, line);) {
            this->map.emplace_back(std::vector<char>(line.begin(), line.end()));
        }
    } catch (const utils::FileReaderError& e) {
        throw error::MapLoaderError(fmt::format("Failed to read map file ({})", mapPath));
    }
}

void game::MapReader::readPlayers(nlohmann::json& json)
{
    if (not json.contains("player")) {
        throw error::MapLoaderError("Cannot find 'player' key.");
    }
    auto& player = json.at("player");

    this->playersInfos.model.modelPath = getString(player, "model", "player.");
    this->playersInfos.model.texturePath = getString(player, "aiTexture", "player.");

    if (not player.contains("textures") or not player.at("textures").is_array()) {
        throw error::MapLoaderError("Cannot find 'player.textures' key as an array.");
    }
    for (const auto& texture : player.at("textures")) {
        if (not texture.is_string()) {
            throw error::MapLoaderError("'player.textures:' value is not a string.");
        }
        std::string str = texture.get<std::string>();
        if (not doesExist(str)) {
            throw error::MapLoaderError(fmt::format("File '{}' not found.", str));
        }
        this->playersInfos.textures.emplace_back(std::move(str));
    }
    if (this->playersInfos.textures.empty()) {
        throw error::MapLoaderError("Cannot have an empty 'player.textures'.");
    }

    auto size = getSize(this->playersInfos.model.modelPath);
    float sizeDiff = getXDifference(size, this->blockSize);
    if (sizeDiff < 0) {
        throw error::MapLoaderError(fmt::format("The player '{}' size should be at least 20% smaller than the reference size. Actually is {}% bigger", this->playersInfos.model.modelPath, std::abs(sizeDiff)));
    }
    if (sizeDiff < 20) {
        throw error::MapLoaderError(fmt::format("The player '{}' size should be at least 20% smaller than the reference size. Current is only {}% smaller", this->playersInfos.model.modelPath, sizeDiff));
    }
    sizeDiff = getZDifference(size, this->blockSize);
    if (sizeDiff < 0) {
        throw error::MapLoaderError(fmt::format("The player '{}' size should be at least 20% smaller than the reference size. Actually is {}% bigger", this->playersInfos.model.modelPath, std::abs(sizeDiff)));
    }
    if (sizeDiff < 20) {
        throw error::MapLoaderError(fmt::format("The player '{}' size should be at least 20% smaller than the reference size. Current is only {}% smaller", this->playersInfos.model.modelPath, sizeDiff));
    }

    this->playersInfos.speed = getFloat(player, "speed", "player.");
    if (this->playersInfos.speed <= 0) {
        throw error::MapLoaderError(fmt::format("The player '{}' speed({}) should be strictly positive.", this->playersInfos.model.modelPath, this->playersInfos.speed));
    }

    if (not player.contains("animation")) {
        throw error::MapLoaderError("Cannot find 'player.animation' key.");
    }
    auto& animation = player.at("animation");
    this->playersInfos.model.animationPath = getString(animation, "path", "player.animation.");
    this->playersInfos.model.animationFps = getInt(animation, "fps", "player.animation.");

    if (not player.contains("sounds")) {
        throw error::MapLoaderError("Cannot find 'player.sounds' key.");
    }
    auto& sounds = player.at("sounds");
    this->playersInfos.sounds.damageSound = getString(sounds, "takingDamage", "player.sounds.");
    this->playersInfos.sounds.deathSound = getString(sounds, "die", "player.sounds.");
    this->playersInfos.sounds.dropBombSound = getString(sounds, "dropBomb", "player.sounds.");
    this->playersInfos.sounds.noBombSound = getString(sounds, "noMoreBomb", "player.sounds.");
}

void game::MapReader::readBombs(nlohmann::json& json)
{
    if (not json.contains("bomb")) {
        throw error::MapLoaderError("Cannot find 'bomb' key.");
    }

    auto& bomb = json.at("bomb");

    this->bombsInfos.model.modelPath = getString(bomb, "model", "bomb.");
    this->bombsInfos.model.texturePath = getString(bomb, "texture", "bomb.");
    this->bombsInfos.sound = getString(bomb, "sound", "bomb.");
    this->explosionsInfos.model.modelPath = getString(bomb, "explosionModel", "bomb.");
    this->explosionsInfos.model.texturePath = getString(bomb, "explosionTexture", "bomb.");
    this->explosionsInfos.sound = getString(bomb, "explosionSound", "bomb.");

    auto size = getSize(this->bombsInfos.model.modelPath);
    float sizeDiff = getXDifference(size, this->blockSize);
    if (sizeDiff < 0) {
        throw error::MapLoaderError(fmt::format("The bomb '{}' size should be at least 30% smaller than the reference size. Actually is {}% bigger", this->bombsInfos.model.modelPath, std::abs(sizeDiff)));
    }
    if (sizeDiff < 30) {
        throw error::MapLoaderError(fmt::format("The bomb '{}' size should be at least 30% smaller than the reference size. Current is only {}% smaller", this->bombsInfos.model.modelPath, sizeDiff));
    }
    sizeDiff = getZDifference(size, this->blockSize);
    if (sizeDiff < 0) {
        throw error::MapLoaderError(fmt::format("The bomb '{}' size should be at least 30% smaller than the reference size. Actually is {}% bigger", this->bombsInfos.model.modelPath, std::abs(sizeDiff)));
    }
    if (sizeDiff < 30) {
        throw error::MapLoaderError(fmt::format("The bomb '{}' size should be at least 30% smaller than the reference size. Current is only {}% smaller", this->bombsInfos.model.modelPath, sizeDiff));
    }

    if (not bomb.contains("animation")) {
        throw error::MapLoaderError("Cannot find 'bomb.animation' key.");
    }
    auto& animation = bomb.at("animation");
    this->bombsInfos.model.animationPath = getString(animation, "path", "bomb.animation.");
    this->bombsInfos.model.animationFps = getInt(animation, "fps", "bomb.animation.");

    if (not bomb.contains("explosionAnimation")) {
        throw error::MapLoaderError("Cannot find 'bomb.explosionAnimation' key.");
    }
    auto& explosionAnimation = bomb.at("explosionAnimation");
    this->explosionsInfos.model.animationPath = getString(explosionAnimation, "path", "bomb.explosionAnimation.");
    this->explosionsInfos.model.animationFps = getInt(explosionAnimation, "fps", "bomb.explosionAnimation.");
}

void game::MapReader::readPowerUps(nlohmann::json& json)
{
    if (not json.contains("power-ups")) {
        throw error::MapLoaderError("Cannot find 'power-ups' key.");
    }

    auto& powerUps = json.at("power-ups");
    std::unordered_map<std::string, ModelSoundInfos&> infos = {{"life", this->powerUpsInfos.life}, {"bombRange", this->powerUpsInfos.bombRange}, {"bombNumber", this->powerUpsInfos.bombNumber}, {"speed", this->powerUpsInfos.speed}};

    for (const auto& info : infos) {
        if (not powerUps.contains(info.first)) {
            throw error::MapLoaderError(fmt::format("Cannot find 'power-ups.{}' key.", info.first));
        }
        auto& powerUp = powerUps.at(info.first);

        info.second.model.modelPath = getString(powerUp, "model", fmt::format("power-ups.{}.", info.first));
        info.second.model.texturePath = getString(powerUp, "texture", fmt::format("power-ups.{}.", info.first));
        info.second.sound = getString(powerUp, "sound", fmt::format("power-ups.{}.", info.first));

        if (not powerUp.contains("animation")) {
            throw error::MapLoaderError(fmt::format("Cannot find 'power-ups.{}.animation' key.", info.first));
        }
        auto& animation = powerUp.at("animation");

        info.second.model.animationPath = getString(animation, "path", fmt::format("power-ups.{}.animation.", info.first));
        info.second.model.animationFps = getInt(animation, "fps", fmt::format("power-ups.{}.animation.", info.first));
    }
}

game::ModelSoundInfos game::MapReader::getBombsInfos() const noexcept
{
    return this->bombsInfos;
}

game::ModelSoundInfos game::MapReader::getExplosionsInfos() const noexcept
{
    return this->explosionsInfos;
}

game::PlayersInfos game::MapReader::getPlayersInfos() const noexcept
{
    return this->playersInfos;
}

game::PowerUpsInfos game::MapReader::getPowerUpsInfos() const noexcept
{
    return this->powerUpsInfos;
}
