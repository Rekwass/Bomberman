/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** MapReader
*/

#pragma once

#include "Game/Map/Error.hpp"
#include "Game/Map/ObjectsInfos.hpp"
#include "Game/Map/PartType.hpp"
#include "Vector.hpp"
#include "fmt/core.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace game {

struct PartInfos {
    std::string groundModelPath;
    std::string groundTexturePath;
    PartType type;
    std::string modelPath;
    std::string texturePath;
};

/*
 * Read a map file
 */
class MapReader {
   public:
    MapReader() noexcept = delete;
    MapReader(std::string file, const utils::Vector& maximumMapSize, bool haveFile = true);
    MapReader(MapReader const& other) noexcept = default;
    MapReader(MapReader&& other) noexcept = default;
    ~MapReader() noexcept = default;

    MapReader& operator=(MapReader const& other) noexcept = default;
    MapReader& operator=(MapReader&& other) noexcept = default;

    /*
     * Get the information associated with the given char identifier
     *
     * Return the infos with the model and texture filepaths and the part type
     *
     * c -> The char identifier
     */
    const PartInfos& getInfosFor(char c) const noexcept;
    /*
     * Get the block size
     *
     * Return the size of a block
     */
    const utils::Vector& getBlockSize() const noexcept;
    /*
     * Get the map as a vector of vector of char identifiers
     * Return the map
     */
    const std::vector<std::vector<char>>& getMap() const noexcept;
    /*
     * Get the bombs infos
     *
     * Return the bombs infos
     */
    ModelSoundInfos getBombsInfos() const noexcept;
    /*
     * Get the explosions infos
     *
     * Return the explosions infos
     */
    ModelSoundInfos getExplosionsInfos() const noexcept;
    /*
     * Get the players infos
     *
     * Return the players infos
     */
    PlayersInfos getPlayersInfos() const noexcept;
    /*
     * Get the power ups infos
     *
     * Return the power ups infos
     */
    PowerUpsInfos getPowerUpsInfos() const noexcept;
    /*
     * Check if a file exist
     *
     * Return true if the file exist and false otherwise
     *
     * filePath -> The path to check
     */
    static bool doesExist(std::string_view filePath) noexcept;

   private:
    /*
     * Parse the given json as map file
     *
     * No return value
     *
     * json -> The json to parse
     *
     * maximumMapSize -> The maximum size of the map
     */
    void parseJson(nlohmann::json json, const utils::Vector& maximumMapSize);
    /*
     * Get the reference size
     *
     * No return value
     *
     * json -> The json object
     */
    void getReferenceSize(nlohmann::json& json);
    /*
     * Get the size of a model
     *
     * Return the size of the model as a vector
     *
     * modelPath -> The file path to the model
     */
    static utils::Vector getSize(std::string modelPath) noexcept;
    /*
     * Get the difference in percentage of two model sizes in the X axis
     *
     * Return the difference as a percentage on the x axis
     *
     * size1 -> The size of the first object
     *
     * size2 -> The size of the second object
     */
    static float getXDifference(utils::Vector size1, utils::Vector size2) noexcept;
    /*
     * Get the difference in percentage of two model sizes in the Z axis
     *
     * Return the difference as a percentage of the z axis
     *
     * size1 -> The size of the first object
     *
     * size2 -> The size of the second object
     */
    static float getZDifference(utils::Vector size1, utils::Vector size2) noexcept;
    /*
     * Get the difference in percentage of two model sizes
     *
     * Return the difference as a percentage of the highest between x and z
     *
     * size1 -> The size of the first object
     *
     * size2 -> The size of the second object
     */
    static float getHighestDifference(utils::Vector size1, utils::Vector size2) noexcept;
    /*
     * Check if the map is valid:
     *
     * Contain only declared identifiers, contain exactly 4 players identifiers
     *
     * Return true if the map is valid, false otherwise
     *
     * maximumMapSize -> The maximum size of the map
     */
    bool checkMapValidity(utils::Vector maximumMapSize) const;
    /*
     * Read the map file
     *
     * No return value
     *
     * json -> The json object
     */
    void readMap(nlohmann::json& json);
    /*
     * Read players information
     *
     * No return value
     *
     * json -> The json object
     */
    void readPlayers(nlohmann::json& json);
    /*
     * Read bombs information
     *
     * No return value
     *
     * json -> The json object
     */
    void readBombs(nlohmann::json& json);
    /*
     * Read power ups information
     *
     * No return value
     *
     * json -> The json object
     */
    void readPowerUps(nlohmann::json& json);
    /*
     * Gets an int from a json array
     *
     * Returns the int value of the given key
     *
     * array -> json array
     *
     * key -> json element key
     *
     * prefix -> The prefix of the label
     */
    static int getInt(nlohmann::json element, std::string_view key, std::string_view prefix = "");
    /*
     * Gets a float from a json array
     *
     * Returns the float value of the given key
     *
     * array -> json array
     *
     * key -> json element key
     *
     * prefix -> The prefix of the label
     */
    static float getFloat(nlohmann::json element, std::string_view key, std::string_view prefix = "");
    /*
     * Gets a string from a json array
     *
     * Returns the string value of the given key
     *
     * array -> json array
     *
     * key -> json element key
     *
     * prefix -> The prefix of the label
     */
    static std::string getString(nlohmann::json element, std::string_view key, std::string_view prefix = "");
    /*
     * Gets a char from a json array
     *
     * Returns the char value of the given key
     *
     * array -> json array
     *
     * key -> json element key
     *
     * prefix -> The prefix of the label
     */
    static char getChar(nlohmann::json element, std::string_view key, std::string_view prefix = "");
    /*
     * Parse walls from the given JSON
     *
     * No return value
     *
     * walls -> value as a std::string
     */
    void parseWalls(nlohmann::json& walls);
    /*
     * Parse grounds from the given JSON
     *
     * No return value
     *
     * grounds -> value as a std::string
     */
    void parseGrounds(nlohmann::json& grounds);
    /*
     * Parse boxes from the given JSON
     *
     * No return value
     *
     * boxes -> value as a std::string
     */
    void parseBoxes(nlohmann::json& boxes);
    /*
     * Parse players from the given JSON
     *
     * No return value
     *
     * players -> value as a std::string
     */
    void parsePlayers(nlohmann::json& players);

    utils::Vector blockSize;
    ModelSoundInfos bombsInfos;
    ModelSoundInfos explosionsInfos;
    PlayersInfos playersInfos;
    PowerUpsInfos powerUpsInfos;
    std::unordered_map<char, PartInfos> parts;
    std::vector<std::vector<char>> map;
};

} // namespace game
