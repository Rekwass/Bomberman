/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableCubicMap3d
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * 2D images renderable as a 3d cubic map data
 */
class RenderableCubicMap3d {
   public:
    RenderableCubicMap3d() noexcept = default;
    RenderableCubicMap3d(std::string_view mapPath, std::string_view atlasPath, utils::Vector size = {1, 1, 1}) noexcept;
    RenderableCubicMap3d(RenderableCubicMap3d const& other) noexcept = default;
    RenderableCubicMap3d(RenderableCubicMap3d&& other) noexcept;
    ~RenderableCubicMap3d() noexcept;

    RenderableCubicMap3d& operator=(RenderableCubicMap3d const& other) noexcept = default;
    RenderableCubicMap3d& operator=(RenderableCubicMap3d&& other) noexcept;

    /*
     * Get the 3d model
     *
     * Return a reference to the 3d model
     */
    const Model& getModel() const;
    /*
     * Recreate the cubic map with a different file
     *
     * No return value
     *
     * mapPath -> The path of the cubic map to load
     *
     * size -> The size of the cubic map parts
     */
    void setMap(std::string_view mapPath, utils::Vector size);
    /*
     * Assign a new texture to the cubic map
     *
     * No return value
     *
     * atlasPath -> The path of the texture atlas to apply on the cubic map parts
     */
    void setTexture(std::string_view atlasPath);

   private:
    bool valid = false;
    Texture2D texture{};
    Model model{};
};

} // namespace ecs::component
