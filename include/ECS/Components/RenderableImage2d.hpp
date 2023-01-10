/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableImage2d
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * 2D images renderable data
 */
class RenderableImage2d {
   public:
    RenderableImage2d() noexcept = default;
    explicit RenderableImage2d(std::string_view imagePath) noexcept;
    RenderableImage2d(RenderableImage2d const& other) noexcept = default;
    RenderableImage2d(RenderableImage2d&& other) noexcept;
    ~RenderableImage2d() noexcept = default;

    RenderableImage2d& operator=(RenderableImage2d const& other) noexcept = default;
    RenderableImage2d& operator=(RenderableImage2d&& other) noexcept;

    /*
     * Get the 2d texture
     *
     * Return a reference to the 2d texture
     */
    const Texture2D& getTexture() const;
    /*
     * Set a new texture for the image
     *
     * No return value
     *
     * imagePath -> The path to the image file
     */
    void setTexture(std::string_view imagePath) noexcept;
    /*
     * Get the size of the 2d image
     *
     * Return the size as a vector (only x and y count)
     */
    utils::Vector getSize() const noexcept;

   private:
    bool valid = false;
    Texture2D texture{};
};

} // namespace ecs::component
