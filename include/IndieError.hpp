/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** IndieError
*/

#pragma once

#include <exception>
#include <string>

namespace error {

class IndieError final : public std::exception {
   public:
    IndieError() noexcept = delete;
    explicit IndieError(std::string const& message);
    IndieError(IndieError const& other) = delete;
    IndieError(IndieError&& other) = delete;
    ~IndieError() override = default;

    IndieError& operator=(IndieError const& other) = delete;
    IndieError& operator=(IndieError&& other) = delete;

    /*
     * Return the error message
     */
    const char* what() const noexcept final;

   protected:
    /*
     * Message that describe the error
     */
    std::string message;
};

} // namespace error
