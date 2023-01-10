/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Error
*/

#include "Game/Map/Error.hpp"

error::MapLoaderError::MapLoaderError(std::string const& message) :
    message(message)
{
}

const char* error::MapLoaderError::what() const noexcept
{
    return this->message.c_str();
}
