/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Main Menu Scene
*/

#pragma once

#include "ECS/Components/Attributes.hpp"
#include "ECS/Components/Music.hpp"
#include "ECS/Components/RenderableImage2d.hpp"
#include "ECS/Components/RenderableText2d.hpp"
#include "ECS/Core/Coordinator.hpp"
#include "ECS/Core/Entities.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/ScenesManager.hpp"
#include "Vector.hpp"
#include "raylib.h"

#include <cstdlib>

namespace scene {

class SettingsScene final : public IScene {
   public:
    SettingsScene() noexcept = delete;
    explicit SettingsScene(ecs::Coordinator& coordinator);
    SettingsScene(SettingsScene const& other) noexcept = delete;
    SettingsScene(SettingsScene&& other) noexcept = delete;
    ~SettingsScene() noexcept override;

    SettingsScene& operator=(SettingsScene const& other) noexcept = delete;
    SettingsScene& operator=(SettingsScene&& other) noexcept = delete;

    void update(ScenesManager& scenesManager, float dt) final;
    utils::Vector getCameraPosition() const noexcept final;
    utils::Vector getCameraLooking() const noexcept final;

    /*
     * Set a fps frame
     *
     * Return true if the valud has been changed, false otherwise
     *
     * fps -> The fps to change value for
     */
    bool changeFps(int fps) noexcept;
    /*
     * Apply fps setting
     *
     * No return value
     */
    void applyFps() noexcept;
    /*
     * Set a monitor
     *
     * Return true if the valud has been changed, false otherwise
     *
     * monitor -> The monitor to change
     */
    bool changeMonitor(int monitor) noexcept;
    /*
     * Apply monitor setting
     *
     * No return value
     */
    void applyMonitor() noexcept;
    /*
     * Change the audio toggle
     *
     * No return value
     *
     * state -> The new state of the audio
     */
    void changeAudio(bool state) noexcept;
    /*
     * Apply the audio setting
     *
     * No return value
     */
    void applyAudio() noexcept;
    /*
     * Change the fullscreen toggle
     *
     * No return value
     *
     * state -> The new state of the fullscreen
     */
    void changeFullscreen(bool state) noexcept;
    /*
     * Apply the fullscreen setting
     *
     * No return value
     */
    void applyFullscreen() noexcept;

   private:
    ecs::Coordinator& coordinator;
    ecs::Entity title{};
    int fpsValue = 60;
    ecs::Entity fps{};
    ecs::Entity fpsLabel{};
    ecs::Entity fpsLeftArrow{};
    ecs::Entity fpsRightArrow{};
    int monitorValue = 0;
    ecs::Entity monitor{};
    ecs::Entity monitorLabel{};
    ecs::Entity monitorLeftArrow{};
    ecs::Entity monitorRightArrow{};
    bool audioValue = true;
    ecs::Entity audio{};
    ecs::Entity audioLabel{};
    ecs::Entity audioLeftArrow{};
    ecs::Entity audioRightArrow{};
    bool fullscreenValue = true;
    ecs::Entity fullscreen{};
    ecs::Entity fullscreenLabel{};
    ecs::Entity fullscreenLeftArrow{};
    ecs::Entity fullscreenRightArrow{};
    ecs::Entity returnButton{};
    ecs::Entity applyButton{};
    ecs::Entity defaultButton{};
    int focus;
    int maxFields;
};

} // namespace scene
