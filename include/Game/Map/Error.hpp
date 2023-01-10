/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Error
*/

#pragma once

#include <exception>
#include <string>

namespace error {

class MapLoaderError final : public std::exception {
   public:
    MapLoaderError() noexcept = delete;
    explicit MapLoaderError(std::string const& message);
    MapLoaderError(MapLoaderError const& other) = delete;
    MapLoaderError(MapLoaderError&& other) = delete;
    ~MapLoaderError() override = default;

    MapLoaderError& operator=(MapLoaderError const& other) = delete;
    MapLoaderError& operator=(MapLoaderError&& other) = delete;

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
