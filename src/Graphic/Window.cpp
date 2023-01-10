/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Window
*/

#include "Graphic/Window.hpp"

#include <string>

graphic::Window::Window(std::string_view windowName, int fps) noexcept
{
    graphic::Window::initWindow(windowName, 0, 0, fps);
}

graphic::Window::Window(int windowWidth, int windowHeight, std::string_view windowName, int fps) noexcept
{
    graphic::Window::initWindow(windowName, windowWidth, windowHeight, fps);
}

graphic::Window::~Window() noexcept
{
    CloseWindow();
}

void graphic::Window::initWindow(std::string_view windowName, int windowWidth, int windowHeight, int fps) noexcept
{
    std::string waitingText = "Loading...";

    SetTargetFPS(fps);
    InitWindow(windowWidth, windowHeight, windowName.data());

    if (windowHeight == 0) {
        windowHeight = GetScreenHeight();
    }
    if (windowWidth == 0) {
        windowWidth = GetScreenWidth();
    }

    SetWindowSize(windowWidth, windowHeight);

    int fontSize = windowHeight / 10;

    BeginDrawing();
    {
        ClearBackground(BLACK);

        DrawText(waitingText.c_str(), (windowWidth - MeasureText(waitingText.c_str(), fontSize)) / 2, (windowHeight - fontSize) / 2, fontSize, WHITE);
    }
    EndDrawing();
}

// NOLINTNEXTLINE
void graphic::Window::setFullScreen(bool fullscreen) const noexcept
{
    if (fullscreen) {
        if (not IsWindowFullscreen()) {
            ToggleFullscreen();
        }
    } else {
        if (IsWindowFullscreen()) {
            ToggleFullscreen();
        }
    }
}

// NOLINTNEXTLINE
void graphic::Window::setMaximized() const noexcept
{
    MaximizeWindow();
}

// NOLINTNEXTLINE
bool graphic::Window::shouldClose() const noexcept
{
    return WindowShouldClose();
}

// NOLINTNEXTLINE
void graphic::Window::setWindowLogo(std::string_view path) noexcept
{
    SetWindowIcon(LoadImage(path.data()));
}
