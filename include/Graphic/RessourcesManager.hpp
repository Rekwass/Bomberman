/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RessourcesManager
*/

#pragma once

#include "raylib.h"

#include <string>
#include <unordered_map>

namespace graphic {

/*
 * Manage ressources (fonts, textures)
 */
class RessourcesManager {
   public:
    RessourcesManager(RessourcesManager const& other) noexcept = delete;
    RessourcesManager(RessourcesManager&& other) noexcept = delete;
    ~RessourcesManager() noexcept;

    RessourcesManager& operator=(RessourcesManager const& other) noexcept = delete;
    RessourcesManager& operator=(RessourcesManager&& other) noexcept = delete;

    /*
     * Add a new texture to the manager
     *
     * Return a reference to the texture
     *
     * filePath -> The path to the texture file
     */
    static Texture2D& getTexture(const std::string& filePath) noexcept;
    /*
     * Add a new font to the manager
     *
     * Return a reference to the font
     *
     * filePath -> The path to the font file
     */
    static Font& getFont(const std::string& filePath) noexcept;

   private:
    RessourcesManager() noexcept = default;
    /*
     * Get the ressources manager unique instance
     *
     * Return the instance
     */
    static RessourcesManager& getInstance() noexcept;
    /*
     * Add a new texture in the ressources manager if needed
     *
     * Return the texture
     *
     * filePath -> The path to the texture file
     */
    Texture2D& getAndCreateTexture(const std::string& filePath) noexcept;
    /*
     * Add a new font in the ressources manager if needed
     *
     * Return the font
     *
     * filePath -> The path to the font file
     */
    Font& getAndCreateFont(const std::string& filePath) noexcept;

    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Font> fonts;
};

} // namespace graphic
