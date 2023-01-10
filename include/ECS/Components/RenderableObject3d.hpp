/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableObject3d
*/

#pragma once

#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * 3D objects renderable data
 */
class RenderableObject3d {
   public:
    RenderableObject3d() noexcept = default;
    RenderableObject3d(std::string_view modelPath, std::string_view texturePath) noexcept;
    RenderableObject3d(RenderableObject3d const& other) noexcept = default;
    RenderableObject3d(RenderableObject3d&& other) noexcept;
    ~RenderableObject3d() noexcept;

    RenderableObject3d& operator=(RenderableObject3d const& other) noexcept = default;
    RenderableObject3d& operator=(RenderableObject3d&& other) noexcept;

    /*
     * Get the 3d model
     *
     * Return a reference to the 3d model
     */
    const Model& getModel() const;
    /*
     * Recreate the model with a different file
     *
     * No return value
     *
     * modelPath -> The path of model file to load
     */
    void setModel(std::string_view modelPath);
    /*
     * Assign a new texture to the model
     *
     * No return value
     *
     * texturePath -> The path of the texture file to apply on the model
     */
    void setTexture(std::string_view texturePath);

   private:
    bool valid = false;
    Model model{};
    Texture2D texture{};
};

} // namespace ecs::component
