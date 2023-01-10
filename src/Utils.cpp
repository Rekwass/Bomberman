/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Utils
*/

#include "Utils.hpp"

#include "AudioPlayer.hpp"
#include "ECS/Components/Animation.hpp"
#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Bounds3d.hpp"
#include "ECS/Components/Camera.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableObject3d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "ECS/Components/Transform.hpp"
#include "ECS/Core/Events.hpp"
#include "Graphic/HitboxDisplayer.hpp"
#include "Graphic/PointDisplayer.hpp"

#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <string>

void utils::setRaylibLogLevel() noexcept
{
    // NOLINTNEXTLINE
    const char* rayDebuging = std::getenv("RAYLOGDEBUG");

    if (rayDebuging == nullptr) {
        SetTraceLogLevel(LOG_WARNING | LOG_ERROR);
    } else {
        SetTraceLogLevel(LOG_ALL);
    }
}

ecs::Coordinator utils::initCoordinator()
{
    ecs::Coordinator coordinator;

    coordinator.registerComponent<ecs::component::Attributes>();
    coordinator.registerComponent<ecs::component::Transform>();
    coordinator.registerComponent<ecs::component::Animation>();
    coordinator.registerComponent<ecs::component::Bounds3d>();
    coordinator.registerComponent<ecs::component::RenderableObject3d>();
    coordinator.registerComponent<ecs::component::RenderableImage2d>();
    coordinator.registerComponent<ecs::component::RenderableText2d>();
    coordinator.registerComponent<ecs::component::Camera>();
    coordinator.registerComponent<ecs::component::MusicObject>();

    return std::move(coordinator);
}

void utils::initEventsListeners(ecs::Coordinator& coordinator, graphic::Renderer& renderer, graphic::Window& window) noexcept
{
    coordinator.addEventListener(ecs::Events::DEBUG_ON, &graphic::HitboxDisplayer::enable, true);
    coordinator.addEventListener(ecs::Events::DEBUG_OFF, &graphic::HitboxDisplayer::enable, false);
    coordinator.addEventListener(ecs::Events::DEBUG_ON, &graphic::PointDisplayer::enable, true);
    coordinator.addEventListener(ecs::Events::DEBUG_OFF, &graphic::PointDisplayer::enable, false);
    coordinator.addEventListener(ecs::Events::DEBUG_ON, &graphic::Renderer::displayFPS, &renderer, true);
    coordinator.addEventListener(ecs::Events::DEBUG_OFF, &graphic::Renderer::displayFPS, &renderer, false);
    coordinator.addEventListener(ecs::Events::AUDIO_ON, &audio::AudioPlayer::enable, true);
    coordinator.addEventListener(ecs::Events::AUDIO_OFF, &audio::AudioPlayer::enable, false);
    coordinator.addEventListener(ecs::Events::FULLSCREEN_ON, &graphic::Window::setFullScreen, &window, true);
    coordinator.addEventListener(ecs::Events::FULLSCREEN_OFF, &graphic::Window::setFullScreen, &window, false);
}

static bool printUsage() noexcept
{
    std::cout << "USAGE: ./bomberman" << std::endl;
    return true;
}

bool utils::checkUsage(int ac, const char* av[]) noexcept
{
    for (int i = 0; i < ac; i++) {
        std::string arg = av[i];
        if (arg == "-h" or arg == "--help") {
            return printUsage();
        }
    }
    return false;
}

void utils::checkKeyboardInputs(ecs::Coordinator& coordinator) noexcept
{
    static bool debug = false;
    static bool pressed = false;

    if (pressed) {
        if (IsKeyUp(KEY_F3)) {
            pressed = false;
        }
    } else {
        if (IsKeyDown(KEY_F3)) {
            debug = not debug;
            coordinator.sendEvent((debug ? ecs::Events::DEBUG_ON : ecs::Events::DEBUG_OFF));
            pressed = true;
        }
    }
}

float utils::getInsideBorder(float x) noexcept
{
    float y = static_cast<int>(x) % 360 + (x - static_cast<int>(x));

    return (y < 0 ? y + 360 : y);
}

float utils::getVectorMin(utils::Vector& vector) noexcept
{
    if (vector.x <= vector.y and vector.x <= vector.z) {
        return vector.x;
    }
    if (vector.x > vector.y and vector.y <= vector.z) {
        return vector.y;
    }
    return vector.z;
}
