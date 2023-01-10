/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableImage3d
*/

#pragma once

#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * 3D images renderable data
 */
class RenderableImage3d {
   public:
    RenderableImage3d() noexcept = default;
    explicit RenderableImage3d(std::string_view imagePath) noexcept;
    RenderableImage3d(RenderableImage3d const& other) noexcept = default;
    RenderableImage3d(RenderableImage3d&& other) noexcept;
    ~RenderableImage3d() noexcept = default;

    RenderableImage3d& operator=(RenderableImage3d const& other) noexcept = default;
    RenderableImage3d& operator=(RenderableImage3d&& other) noexcept;

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

   private:
    bool valid = false;
    Texture2D texture{};
};

} // namespace ecs::component
