/*
** EPITECH PROJECT, 2022
** include
** File description:
** SettingsManager
*/

#pragma once

#include "ECS/Core/Coordinator.hpp"

#include <memory>

namespace game {

/*
 * Manage game settings
 */
class SettingsManager {
   public:
    SettingsManager() noexcept = delete;
    SettingsManager(SettingsManager const& other) noexcept = delete;
    SettingsManager(SettingsManager&& other) noexcept = delete;
    ~SettingsManager() noexcept;

    SettingsManager& operator=(SettingsManager const& other) noexcept = delete;
    SettingsManager& operator=(SettingsManager&& other) noexcept = delete;

    /*
     * Init the settings manager
     *
     * No return value
     *
     * coordinator -> The ECS coordinator
     */
    static void init(ecs::Coordinator& coordinator) noexcept;
    /*
     * Get the fps
     *
     * Return the fps
     */
    static int getFps() noexcept;
    /*
     * Get the monitor id
     *
     * Return the used monitor id
     */
    static int getMonitor() noexcept;
    /*
     * Get if the audio is enabled
     *
     * Return true if the audio is active, falst otherwise
     */
    static bool getAudioState() noexcept;
    /*
     * Get if the fullscreen is enabled
     *
     * Return true if the fullscreen is active, falst otherwise
     */
    static bool getFullscreenState() noexcept;
    /*
     * Set the fps setting
     *
     * No return value
     *
     * fps -> The new fps to
     */
    static void setFps(int fps) noexcept;
    /*
     * Set the used monitor
     *
     * No return value
     *
     * monitorId -> The monitor id to use
     */
    static void setMonitor(int monitorId) noexcept;
    /*
     * Set if the audio is enabled
     *
     * No return value
     *
     * state -> Set to true if the audio should be enabled, false otherwise
     */
    static void setAudioState(bool state) noexcept;
    /*
     * Set if the fullscreen is enabled
     *
     * No return value
     *
     * state -> Set to true if the fullscreen should be enabled, false otherwise
     */
    static void setFullscreenState(bool state) noexcept;

   private:
    explicit SettingsManager(ecs::Coordinator& coordinator);
    /*
<<<<<<< HEAD
     * Get the unique instance of the sound player
=======
     * Apply the fps
>>>>>>> ace9f4a46972f4d1d174ee098075d2369a9d2d59
     *
     * No return value
     */
    void applyFps() const noexcept;
    /*
     * Apply the monitor
     *
     * No return value
     */
    void applyMonitor() const noexcept;
    /*
     * Apply the audio
     *
     * No return value
     */
    void applyAudio() const noexcept;
    /*
     * Apply the fullscreen
     *
     * No return value
     */
    void applyFullscreen() const noexcept;

    static std::unique_ptr<SettingsManager> instance;
    ecs::Coordinator& coordinator;
    int fps = 0;
    int monitor = 0;
    bool audio = true;
    bool fullscreen = true;
};

} // namespace game
