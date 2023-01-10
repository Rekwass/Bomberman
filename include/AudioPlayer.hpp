/*
** EPITECH PROJECT, 2022
** include
** File description:
** AudioPlayer
*/

#pragma once

#include "raylib.h"

#include <string>
#include <string_view>
#include <unordered_map>

namespace audio {

/*
 * Audio player
 */
class AudioPlayer {
   public:
    AudioPlayer(AudioPlayer const& other) noexcept = delete;
    AudioPlayer(AudioPlayer&& other) noexcept = delete;
    ~AudioPlayer() noexcept;

    AudioPlayer& operator=(AudioPlayer const& other) noexcept = delete;
    AudioPlayer& operator=(AudioPlayer&& other) noexcept = delete;

    /*
     * Init the audio player if not already
     *
     * No return value
     */
    static void Init() noexcept;
    /*
     * Enable or not the audio player
     *
     * No return value
     *
     * state -> Set to true if the sounds should be enabled, false otherwise
     */
    static void enable(bool state) noexcept;
    /*
     * Play a sound
     *
     * No return value
     *
     * soundPath -> The filepath of the sound
     */
    static void playSound(std::string_view soundPath) noexcept;
    /*
     * Set the volume of the given sound
     *
     * No return value
     *
     * soundPath -> The filepath of the sound
     *
     * volume -> The volume to set on the sound
     */
    static void setSoundVolume(std::string_view soundPath, float volume) noexcept;

   private:
    AudioPlayer() noexcept;

    /*
     * Get the unique instance of the sound player
     *
     * Return the instance
     */
    static AudioPlayer& getInstance() noexcept;

    std::unordered_map<std::string, Sound> sounds;
};

} // namespace audio
