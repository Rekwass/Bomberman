/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableRelief3d
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * 2D images renderable as a 3d relief data
 */
class RenderableRelief3d {
   public:
    RenderableRelief3d() noexcept = default;
    explicit RenderableRelief3d(std::string_view reliefPath, utils::Vector size, Color color) noexcept;
    RenderableRelief3d(RenderableRelief3d const& other) noexcept = default;
    RenderableRelief3d(RenderableRelief3d&& other) noexcept;
    ~RenderableRelief3d() noexcept;

    RenderableRelief3d& operator=(RenderableRelief3d const& other) noexcept = default;
    RenderableRelief3d& operator=(RenderableRelief3d&& other) noexcept;

    /*
     * Get the 3d model
     *
     * Return a reference to the 3d model
     */
    const Model& getModel() const noexcept;
    /*
     * Get the 3d relief color
     *
     * Return a reference to the 3d relief color
     */
    const Color& getColor() const noexcept;

    /*
     * Set a new color for the 3d relief
     *
     * No return value
     *
     * color -> The new color to assign to the 3d relief
     */
    void setColor(Color color) noexcept;
    /*
     * Assign a new texture to the model
     *
     * No return value
     *
     * reliefPath -> The path of the texture file to apply on the model
     *
     * size -> The size of the relief
     *
     * color -> The color of the relief
     */
    void setRelief(std::string_view reliefPath, utils::Vector size, Color color) noexcept;

   private:
    bool valid = false;
    Color color{};
    Texture2D relief{};
    Model model{};
};

} // namespace ecs::component
