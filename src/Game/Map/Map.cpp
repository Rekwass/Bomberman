/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Map
*/

#include "Game/Map/Map.hpp"

#include "Game/Map/Player/AIPlayer.hpp"
#include "Game/Map/Player/KeyBoardPlayer.hpp"
#include "Game/Map/Player/OnlinePlayer.hpp"
#include "Game/Map/PowerUp/APowerUp.hpp"
#include "Graphic/HitboxDisplayer.hpp"
#include "Graphic/PointDisplayer.hpp"

game::Map::Map(ecs::Coordinator& coordinator, ecs::system::CollisionSystem& collisionSystem, const MapReader& mapReader, const utils::Vector& mapPosition) :
    coordinator(coordinator), collisionSystem(collisionSystem)
{
    const auto& map = mapReader.getMap();
    this->blockSize = mapReader.getBlockSize();
    this->bombsInfos = mapReader.getBombsInfos();
    this->explosionsInfos = mapReader.getExplosionsInfos();
    this->powerUpsInfos = mapReader.getPowerUpsInfos();
    auto playersInfos = mapReader.getPlayersInfos();
    this->mapStarting = mapPosition - utils::Vector{-((this->blockSize.x * map.size()) / 2), 0, (this->blockSize.z * map.at(0).size()) / 2};
    utils::Vector centerZero = this->mapStarting + utils::Vector{-(this->blockSize.x / 2), 0, this->blockSize.z / 2};

    game::PlayerId playerId = 1;
    for (int i = 0; const auto& line : map) {
        this->mapParts.emplace_back();
        for (int y = 0; const auto& c : line) {
            const auto& infos = mapReader.getInfosFor(c);
            auto position = centerZero + (blockSize * utils::Vector{-static_cast<float>(i), 0, static_cast<float>(y)});

            this->grounds.emplace_back(coordinator, infos.groundModelPath, infos.groundTexturePath, position);
            // NOLINTNEXTLINE
            if (infos.type == PartType::PLAYER) {
                this->mapParts.at(i).emplace_back(PartType::GROUND);
                switch (game::PlayersManager::getPlayerType(playerId)) {
                case PlayerType::KEYBOARD:
                    this->players.emplace_back(std::make_unique<KeyBoardPlayer>(coordinator, playersInfos, game::PlayersManager::getPlayerTexture(playerId), position, playerId, game::PlayersManager::getPlayerKeys(playerId), *this));
                    break;
                case PlayerType::AI:
                    this->players.emplace_back(std::make_unique<AIPlayer>(coordinator, playersInfos, position, playerId, *this));
                    break;
                case PlayerType::NETWORK:
                    this->players.emplace_back(std::make_unique<OnlinePlayer>(coordinator, playersInfos, position, playerId, *this));
                    break;
                default:
                    break;
                }
                playerId++;
            } else if (infos.type != PartType::GROUND) {
                this->mapParts.at(i).emplace_back(coordinator, collisionSystem, infos.modelPath, infos.texturePath, infos.type, position);
            } else {
                this->mapParts.at(i).emplace_back(PartType::GROUND);
            }
            y++;
        }
        i++;
    }
}

void game::Map::update()
{
    for (const auto& player : this->players) {
        Position indexes = this->convertVectorAsPosition(player->getPosition());
        auto& part = this->mapParts.at(indexes.x).at(indexes.y);
        auto state = part.getPartState();

        switch (state) {
        case PartState::FIRE:
            if (player->isAlive()) {
                player->takeDamage();
            }
            break;
        case PartState::POWER_UP:
            part.applyPowerUp(*player);
            break;
        default:
            break;
        }
        player->update();
    }
    for (auto& partsLine : this->mapParts) {
        for (auto& part : partsLine) {
            part.update();
        }
    }
    this->updateBombs();
}

void game::Map::updateBombs() noexcept
{
    for (auto it = this->bombs.begin(); it != this->bombs.end();) {
        if (it->second.shouldExplose()) {
            it->second.explose();
            this->mapParts.at(it->first.x).at(it->first.y).setPartState(PartState::FREE);
            this->mapParts.at(it->first.x).at(it->first.y).setOnFire(this->coordinator, this->explosionsInfos.model, it->second.getPosition());

            auto range = this->getRange(it->first, it->second.getRange());
            BombId id = it->second.getId();

            for (int i = 1; i <= range.up; i++) {
                auto& part = this->mapParts.at(it->first.x - i).at(it->first.y);
                if (part.getPartState() == PartState::BOMB) {
                    this->bombs.at({it->first.x - i, it->first.y}).explose();
                }
                part.removeDanger(id);
                part.setOnFire(this->coordinator, this->explosionsInfos.model, it->second.getPosition() + utils::Vector{this->blockSize.x * i, 0, 0});
            }
            if (range.haveUp) {
                this->mapParts.at(it->first.x - (range.up + 1)).at(it->first.y).explose(this->coordinator, this->powerUpsInfos, this->explosionsInfos.sound);
            }

            for (int i = 1; i <= range.down; i++) {
                auto& part = this->mapParts.at(it->first.x + i).at(it->first.y);
                if (part.getPartState() == PartState::BOMB) {
                    this->bombs.at({it->first.x + i, it->first.y}).explose();
                }
                part.removeDanger(id);
                part.setOnFire(this->coordinator, this->explosionsInfos.model, it->second.getPosition() - utils::Vector{this->blockSize.x * i, 0, 0});
            }
            if (range.haveDown) {
                this->mapParts.at(it->first.x + (range.down + 1)).at(it->first.y).explose(this->coordinator, this->powerUpsInfos, this->explosionsInfos.sound);
            }

            for (int i = 1; i <= range.left; i++) {
                auto& part = this->mapParts.at(it->first.x).at(it->first.y - i);
                if (part.getPartState() == PartState::BOMB) {
                    this->bombs.at({it->first.x, it->first.y - i}).explose();
                }
                part.removeDanger(id);
                part.setOnFire(this->coordinator, this->explosionsInfos.model, it->second.getPosition() - utils::Vector{0, 0, this->blockSize.z * i});
            }
            if (range.haveLeft) {
                this->mapParts.at(it->first.x).at(it->first.y - (range.left + 1)).explose(this->coordinator, this->powerUpsInfos, this->explosionsInfos.sound);
            }

            for (int i = 1; i <= range.right; i++) {
                auto& part = this->mapParts.at(it->first.x).at(it->first.y + i);
                if (part.getPartState() == PartState::BOMB) {
                    this->bombs.at({it->first.x, it->first.y + i}).explose();
                }
                part.removeDanger(id);
                part.setOnFire(this->coordinator, this->explosionsInfos.model, it->second.getPosition() + utils::Vector{0, 0, this->blockSize.z * i});
            }
            if (range.haveRight) {
                this->mapParts.at(it->first.x).at(it->first.y + (range.right + 1)).explose(this->coordinator, this->powerUpsInfos, this->explosionsInfos.sound);
            }

            it = this->bombs.erase(it);
        } else {
            it++;
        }
    }
}

bool game::Map::putBomb(utils::Vector position, APlayer& player) noexcept
{
    Position indexes = this->convertVectorAsPosition(position);
    if (this->bombs.contains(indexes)) {
        return false;
    }
    player.useBomb();

    auto center = this->mapStarting + utils::Vector{(-this->blockSize.x) * indexes.x, 0, this->blockSize.z * indexes.y} + utils::Vector{-(this->blockSize.x / 2), 0, this->blockSize.z / 2};
    this->bombs.insert({indexes, Bomb(this->coordinator, this->collisionSystem, this->bombsInfos, center, player)});
    BombId id = this->bombs.at(indexes).getId();

    this->mapParts.at(indexes.x).at(indexes.y).setPartState(PartState::BOMB);

    auto possibleRange = this->getRange(indexes, player.getBombRange());

    for (int i = 1; i <= possibleRange.up; i++) {
        this->mapParts.at(indexes.x - i).at(indexes.y).setDanger(id);
    }
    for (int i = 1; i <= possibleRange.down; i++) {
        this->mapParts.at(indexes.x + i).at(indexes.y).setDanger(id);
    }
    for (int i = 1; i <= possibleRange.left; i++) {
        this->mapParts.at(indexes.x).at(indexes.y - i).setDanger(id);
    }
    for (int i = 1; i <= possibleRange.right; i++) {
        this->mapParts.at(indexes.x).at(indexes.y + i).setDanger(id);
    }

    return true;
}

std::array<game::PlayerStat, 4> game::Map::getPlayersStats() const noexcept
{
    std::array<game::PlayerStat, 4> stats{};

    for (const auto& player : this->players) {
        auto& stat = stats.at(player->getId() - 1);
        stat.lifes = player->getLifes();
        stat.bombs = player->getLeftBombs();
    }
    return stats;
}

game::AroundMapPartStates game::Map::getAroundParts(utils::Vector position) const noexcept
{
    auto indexes = this->convertVectorAsPosition(position);
    AroundMapPartStates around{};

    around.middle = this->mapParts.at(indexes.x).at(indexes.y).getPartState();
    if (this->mapParts.at(indexes.x).at(indexes.y).isInDanger()) {
        around.middle = PartState::DANGER;
    }
    if (indexes.x - 1 >= 0) {
        around.up = this->mapParts.at(indexes.x - 1).at(indexes.y).getPartState();
        if (this->mapParts.at(indexes.x - 1).at(indexes.y).isInDanger()) {
            around.up = PartState::DANGER;
        }
    }
    if (indexes.x + 1 < this->mapParts.size()) {
        around.down = this->mapParts.at(indexes.x + 1).at(indexes.y).getPartState();
        if (this->mapParts.at(indexes.x + 1).at(indexes.y).isInDanger()) {
            around.down = PartState::DANGER;
        }
    }
    if (indexes.y - 1 >= 0) {
        around.left = this->mapParts.at(indexes.x).at(indexes.y - 1).getPartState();
        if (this->mapParts.at(indexes.x).at(indexes.y - 1).isInDanger()) {
            around.left = PartState::DANGER;
        }
    }
    if (indexes.y + 1 < this->mapParts.at(indexes.x).size()) {
        around.right = this->mapParts.at(indexes.x).at(indexes.y + 1).getPartState();
        if (this->mapParts.at(indexes.x).at(indexes.y + 1).isInDanger()) {
            around.right = PartState::DANGER;
        }
    }

    return around;
}

game::AroundMapPartTypes game::Map::getAroundPartsType(utils::Vector position) const noexcept
{
    auto indexes = this->convertVectorAsPosition(position);
    AroundMapPartTypes around{};

    around.middle = this->mapParts.at(indexes.x).at(indexes.y).getPartType();
    if (indexes.x - 1 >= 0) {
        around.up = this->mapParts.at(indexes.x - 1).at(indexes.y).getPartType();
    }
    if (indexes.x + 1 < this->mapParts.size()) {
        around.down = this->mapParts.at(indexes.x + 1).at(indexes.y).getPartType();
    }
    if (indexes.y - 1 >= 0) {
        around.left = this->mapParts.at(indexes.x).at(indexes.y - 1).getPartType();
    }
    if (indexes.y + 1 < this->mapParts.at(indexes.x).size()) {
        around.right = this->mapParts.at(indexes.x).at(indexes.y + 1).getPartType();
    }

    return around;
}

// NOLINTNEXTLINE
game::Position game::Map::convertVectorAsPosition(utils::Vector position) const noexcept
{
    position -= this->mapStarting;
    position /= this->blockSize;
    return {static_cast<int>(std::abs(position.x)), static_cast<int>(std::abs(position.z))};
}

static bool isBoundsInBounds(BoundingBox bounds1, BoundingBox bounds2) noexcept
{
    return (bounds1.min.x >= bounds2.min.x and bounds1.max.x <= bounds2.max.x and bounds1.min.z >= bounds2.min.z and bounds1.max.z <= bounds2.max.z);
}

bool game::Map::isCompletelyInsidePart(utils::Vector position, BoundingBox hitbox, float modifier) const noexcept
{
    utils::Vector delimSize = this->blockSize * modifier;
    auto indexes = this->convertVectorAsPosition(position);
    auto nearest = this->mapStarting + utils::Vector{(-this->blockSize.x) * indexes.x, 0, this->blockSize.z * indexes.y} + utils::Vector{-(this->blockSize.x / 2), 0, this->blockSize.z / 2};

    BoundingBox box = {.min = {nearest.x - (delimSize.x / 2), nearest.y, nearest.z - (delimSize.z / 2)}, .max = {nearest.x + (delimSize.x / 2), nearest.y + delimSize.y, nearest.z + (delimSize.z / 2)}};
    return isBoundsInBounds(hitbox, box);
}

utils::Vector game::Map::getNearestPartCenter(utils::Vector& position) const noexcept
{
    auto indexes = this->convertVectorAsPosition(position);
    utils::Vector nearest = this->mapStarting + utils::Vector{(-this->blockSize.x) * indexes.x, 0, this->blockSize.z * indexes.y} + utils::Vector{-(this->blockSize.x / 2), 0, this->blockSize.z / 2};

    return (nearest);
}

game::Range game::Map::getRange(Position position, unsigned int maximumRange) noexcept
{
    Range range;
    bool up = true;
    bool down = true;
    bool left = true;
    bool right = true;

    for (int i = 1; i <= maximumRange; i++) {
        if (up) {
            if (position.x - i < 0 or this->mapParts.at(position.x - i).at(position.y).getPartState() == PartState::UNFREE) {
                if (position.x - i >= 0) {
                    range.haveUp = true;
                }
                up = false;
            } else {
                range.up++;
            }
        }
        if (down) {
            if (position.x + i >= this->mapParts.size() or this->mapParts.at(position.x + i).at(position.y).getPartState() == PartState::UNFREE) {
                if (position.x + i < this->mapParts.size()) {
                    range.haveDown = true;
                }
                down = false;
            } else {
                range.down++;
            }
        }
        if (left) {
            if (position.y - i < 0 or this->mapParts.at(position.x).at(position.y - i).getPartState() == PartState::UNFREE) {
                if (position.y - i >= 0) {
                    range.haveLeft = true;
                }
                left = false;
            } else {
                range.left++;
            }
        }
        if (right) {
            if (position.y + i >= this->mapParts.at(position.x).size() or this->mapParts.at(position.x).at(position.y + i).getPartState() == PartState::UNFREE) {
                if (position.y + i < this->mapParts.at(position.x).size()) {
                    range.haveRight = true;
                }
                right = false;
            } else {
                range.right++;
            }
        }
    }
    return range;
}

bool game::Map::isEnded() const noexcept
{
    int alivePlayers = 0;

    for (const auto& player : this->players) {
        if (player->isAlive()) {
            alivePlayers++;
        }
    }
    return (alivePlayers < 2);
}

std::vector<std::unique_ptr<game::APlayer>> game::Map::extractPlayers() noexcept
{
    return std::move(this->players);
}
