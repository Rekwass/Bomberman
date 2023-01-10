/*
** EPITECH PROJECT, 2022
** include
** File description:
** ObjectsInfos
*/

#pragma once

#include <string>
#include <vector>

namespace game {

struct ModelInfos {
    std::string modelPath;
    std::string texturePath;
    std::string animationPath;
    int animationFps = 60;
};

struct PlayerSounds {
    std::string damageSound;
    std::string deathSound;
    std::string dropBombSound;
    std::string noBombSound;
};

struct PlayersInfos {
    ModelInfos model;
    float speed = 0;
    PlayerSounds sounds;
    std::vector<std::string> textures;
};

struct ModelSoundInfos {
    ModelInfos model;
    std::string sound;
};

struct PowerUpsInfos {
    ModelSoundInfos life;
    ModelSoundInfos bombRange;
    ModelSoundInfos bombNumber;
    ModelSoundInfos speed;
};

} // namespace game
