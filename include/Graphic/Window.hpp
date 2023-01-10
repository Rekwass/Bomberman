/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Window
*/

#pragma once

#include "raylib.h"

#include <string_view>

namespace graphic {

/*
 * Raylib graphic window
 */
class Window {
   public:
    Window() noexcept = delete;
    explicit Window(std::string_view windowName = "raylib window", int fps = 60) noexcept;
    Window(int windowWidth, int windowHeight, std::string_view windowName = "raylib window", int fps = 60) noexcept;
    Window(Window const& other) noexcept = default;
    Window(Window&& other) noexcept = default;
    ~Window() noexcept;

    Window& operator=(Window const& other) noexcept = default;
    Window& operator=(Window&& other) noexcept = default;

    /*
     * Set the window to full screen
     *
     * No return value
     *
     * fullscreen -> Set to true if the window should be in fullscreen
     */
    void setFullScreen(bool fullscreen = true) const noexcept;
    /*
     * Set the window to maximised
     *
     * No return value
     */
    void setMaximized() const noexcept;
    /*
     * Check if the window should close (Escape pressed or close button)
     *
     * Return true if the window should close, false otherwise
     */
    bool shouldClose() const noexcept;
    /*
     * Change the window logo in the taskbar
     *
     * No return value
     */
    void setWindowLogo(std::string_view path) noexcept;

   private:
    /*
     * Init the raylib window
     *
     * No return value
     *
     * windowName -> The name of the created window
     *
     * windowWidth -> The width of the window
     *
     * windowHeight -> The height of the window
     *
     * fps -> Graphic window fps
     */
    static void initWindow(std::string_view windowName, int windowWidth, int windowHeight, int fps) noexcept;
};

} // namespace graphic
