/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** RenderableText3d
*/

#pragma once

#include "Vector.hpp"
#include "raylib.h"

#include <string>
#include <string_view>

#define RAYLIB_NEW_RLGL

namespace ecs::component {

/*
 * 3D texts renderable data
 */
class RenderableText3d {
   public:
    RenderableText3d() noexcept = default;
    explicit RenderableText3d(std::string_view text, float fontSize = 10, float fontSpacing = 1, float lineSpacing = 1, bool backface = true, Color color = WHITE) noexcept;
    RenderableText3d(std::string_view fontPath, std::string_view text, float fontSize = 10, float fontSpacing = 1, float lineSpacing = 1, bool backface = true, Color color = WHITE) noexcept;
    RenderableText3d(RenderableText3d const& other) noexcept = default;
    RenderableText3d(RenderableText3d&& other) noexcept;
    ~RenderableText3d() noexcept = default;

    RenderableText3d& operator=(RenderableText3d const& other) noexcept = default;
    RenderableText3d& operator=(RenderableText3d&& other) noexcept;

    /*
     * Draw the text
     *
     * No return value
     *
     * position -> The position where to draw the text
     */
    void draw() const noexcept;

   private:
    bool needDestroy = false;
    Font font{};
    std::string text{};
    float fontSize = 10;
    float fontSpacing = 1;
    float lineSpacing = 1;
    bool backface = true;
    Color color = WHITE;
};

} // namespace ecs::component
