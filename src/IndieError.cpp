/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** IndieError
*/

#include "IndieError.hpp"

error::IndieError::IndieError(std::string const& message) :
    message(message)
{
}

const char* error::IndieError::what() const noexcept
{
    return this->message.c_str();
}
