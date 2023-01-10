/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Music
*/

#pragma once

#include "raylib.h"

#include <string_view>

namespace ecs::component {

/*
 * MusicObject
 */
class MusicObject {
   public:
    MusicObject() noexcept = default;
    explicit MusicObject(std::string_view musicPath) noexcept;
    MusicObject(MusicObject const& other) noexcept = delete;
    MusicObject(MusicObject&& other) noexcept;
    ~MusicObject() noexcept;

    MusicObject& operator=(MusicObject const& other) noexcept = delete;
    MusicObject& operator=(MusicObject&& other) noexcept;

    const Music& getMusic() noexcept;

    void play() noexcept;
    void pause() noexcept;
    void restart() noexcept;
    void setVolume(float volume) noexcept;
    void setPitch(float pitch) noexcept;
    void setPause(bool value) noexcept;

   private:
    bool valid = false;
    Music music{};
    bool isPause = false;
    bool isStarted = false;
    bool loop = true;
    float pitch = 1;
};

} // namespace ecs::component
