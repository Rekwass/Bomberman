/*
** EPITECH PROJECT, 2022
** src
** File description:
** RessourcesManager
*/

#include "Graphic/RessourcesManager.hpp"

graphic::RessourcesManager& graphic::RessourcesManager::getInstance() noexcept
{
    static RessourcesManager ressourcesManager;

    return ressourcesManager;
}

graphic::RessourcesManager::~RessourcesManager() noexcept
{
    for (const auto& texture : this->textures) {
        UnloadTexture(texture.second);
    }
    for (const auto& font : this->fonts) {
        UnloadFont(font.second);
    }
}

Texture2D& graphic::RessourcesManager::getTexture(const std::string& filePath) noexcept
{
    return getInstance().getAndCreateTexture(filePath);
}

Font& graphic::RessourcesManager::getFont(const std::string& filePath) noexcept
{
    return getInstance().getAndCreateFont(filePath);
}

Texture2D& graphic::RessourcesManager::getAndCreateTexture(const std::string& filePath) noexcept
{
    if (not this->textures.contains(filePath)) {
        this->textures.insert({filePath, LoadTexture(filePath.c_str())});
    }
    return this->textures.at(filePath);
}

Font& graphic::RessourcesManager::getAndCreateFont(const std::string& filePath) noexcept
{
    if (not this->fonts.contains(filePath)) {
        this->fonts.insert({filePath, LoadFont(filePath.c_str())});
    }
    return this->fonts.at(filePath);
}
