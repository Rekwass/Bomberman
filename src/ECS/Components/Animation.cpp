/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Animation
*/

#include "ECS/Components/Animation.hpp"

#include "ECS/ECSErrors.hpp"
#include "fmt/core.h"

ecs::component::Animation::Animation(std::string_view animationFilePath, unsigned int animationsCount, int fps) :
    fps(fps)
{
    if (fps <= 0) {
        throw ecs::error::ComponentError("Animation", fmt::format("Cannot load an animation with null/negative fps ({})", fps));
    }
    this->valid = true;
    this->animations = LoadModelAnimations(animationFilePath.data(), &this->animationsCount);
    if (this->animationsCount != animationsCount) {
        throw ecs::error::ComponentError("Animation", fmt::format("Give {} animations on the '{}' animation file but it contain {} animations", animationsCount, animationFilePath, this->animationsCount));
    }
}

ecs::component::Animation::Animation(Animation&& other) noexcept
{
    this->valid = other.valid;
    this->backgroundAnimations = std::move(other.backgroundAnimations);
    this->topLevelAnimations = std::move(other.topLevelAnimations);
    this->animations = other.animations;
    this->animationsCount = other.animationsCount;
    this->fps = other.fps;
    other.valid = false;
}

ecs::component::Animation& ecs::component::Animation::operator=(Animation&& other) noexcept
{
    this->valid = other.valid;
    this->backgroundAnimations = std::move(other.backgroundAnimations);
    this->topLevelAnimations = std::move(other.topLevelAnimations);
    this->animations = other.animations;
    this->animationsCount = other.animationsCount;
    this->fps = other.fps;
    other.valid = false;
    return *this;
}

ecs::component::Animation::~Animation() noexcept
{
    if (this->valid) {
        UnloadModelAnimations(this->animations, this->animationsCount);
    }
}

void ecs::component::Animation::setAnimations(std::string_view animationFilePath, unsigned int animationsCount, int fps)
{
    if (fps <= 0) {
        throw ecs::error::ComponentError("Animation", fmt::format("Cannot load an animation with null/negative fps ({})", fps));
    }
    if (this->valid) {
        UnloadModelAnimations(this->animations, this->animationsCount);
    }
    this->valid = true;
    this->fps = fps;
    this->animationsCount = animationsCount;
    this->animations = LoadModelAnimations(animationFilePath.data(), &this->animationsCount);
    this->clear(false, true);
    this->clear(false, false);
}

int ecs::component::Animation::getAnimationsNumber() const noexcept
{
    return this->animationsCount;
}

void ecs::component::Animation::addAnimation(unsigned int animationId, bool background)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Animation", "Use of the object before a correct initialization");
    }
    if (animationId <= 0 or animationId > this->animationsCount) {
        throw ecs::error::ComponentError("Animation", fmt::format("Cannot use the animation {} because only have {} animations", animationId, this->animationsCount));
    }
    if (background) {
        this->backgroundAnimations.animationsQueue.emplace(animationId - 1);
    } else {
        this->topLevelAnimations.animationsQueue.emplace(animationId - 1);
        this->hasPriorityAnimations = true;
    }
    this->startAnimations();
}

void ecs::component::Animation::update(const Model& model, float elapsedTime)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Animation", "Use of the object before a correct initialization");
    }
    auto& animation = (this->hasPriorityAnimations ? this->topLevelAnimations : this->backgroundAnimations);

    if (animation.running and not animation.paused) {
        animation.animationFrameCounter += this->fps * elapsedTime;

        if (animation.animationFrameCounter >= this->animations[animation.usedAnimation].frameCount) {
            if (animation.loopedAnimations.contains(animation.usedAnimation) and not animation.noLoop) {
                animation.animationFrameCounter -= this->animations[animation.usedAnimation].frameCount * (animation.animationFrameCounter / this->animations[animation.usedAnimation].frameCount);
                if (animation.animationFrameCounter >= this->animations[animation.usedAnimation].frameCount) {
                    animation.animationFrameCounter = 0;
                }
            } else {
                this->endAnimation(model);
            }
        }
        UpdateModelAnimation(model, this->animations[animation.usedAnimation], static_cast<int>(animation.animationFrameCounter));
    }
}

void ecs::component::Animation::startAnimations() noexcept
{
    if (this->hasPriorityAnimations and not this->topLevelAnimations.running and this->topLevelAnimations.animationsQueue.empty()) {
        this->hasPriorityAnimations = false;
    }

    if (this->hasPriorityAnimations) {
        if (not this->topLevelAnimations.running) {
            this->topLevelAnimations.running = true;
            this->topLevelAnimations.animationFrameCounter = 0;
            this->topLevelAnimations.usedAnimation = this->topLevelAnimations.animationsQueue.front();
            this->topLevelAnimations.animationsQueue.pop();
            if (this->topLevelAnimations.noLoop and this->topLevelAnimations.noLoopToId == this->topLevelAnimations.usedAnimation) {
                this->topLevelAnimations.noLoop = false;
            }
        }
    } else {
        if (not this->backgroundAnimations.running) {
            this->backgroundAnimations.running = true;
            this->backgroundAnimations.animationFrameCounter = 0;
            this->backgroundAnimations.usedAnimation = this->backgroundAnimations.animationsQueue.front();
            this->backgroundAnimations.animationsQueue.pop();
            if (this->backgroundAnimations.noLoop and this->backgroundAnimations.noLoopToId == this->backgroundAnimations.usedAnimation) {
                this->backgroundAnimations.noLoop = false;
            }
        }
    }
}

void ecs::component::Animation::endAnimation(const Model& model)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Animation", "Use of the object before a correct initialization");
    }
    auto& animation = (this->hasPriorityAnimations ? this->topLevelAnimations : this->backgroundAnimations);

    if (this->hasPriorityAnimations) {
    }
    UpdateModelAnimation(model, this->animations[animation.usedAnimation], this->animations[animation.usedAnimation].frameCount);
    animation.running = false;

    if (not this->topLevelAnimations.animationsQueue.empty() or not this->backgroundAnimations.animationsQueue.empty()) {
        this->startAnimations();
    } else {
        if (this->backgroundAnimations.running) {
            this->hasPriorityAnimations = false;
        }
    }
}

bool ecs::component::Animation::isEnded(bool background) const noexcept
{
    return (not(background ? this->backgroundAnimations : this->topLevelAnimations).running);
}

void ecs::component::Animation::loop(unsigned int animationId, bool looping, bool background)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Animation", "Use of the object before a correct initialization");
    }
    if (animationId <= 0 or animationId > this->animationsCount) {
        throw ecs::error::ComponentError("Animation", fmt::format("Cannot use the animation {} because only have {} animations", animationId, this->animationsCount));
    }
    auto& animation = (background ? this->backgroundAnimations : this->topLevelAnimations);
    if (looping) {
        animation.loopedAnimations.emplace(animationId - 1);
    } else {
        animation.loopedAnimations.erase(animationId - 1);
    }
}

void ecs::component::Animation::noLoopTo(unsigned int animationId, bool background)
{
    if (not this->valid) {
        throw ecs::error::ComponentError("Animation", "Use of the object before a correct initialization");
    }
    if (animationId <= 0 or animationId > this->animationsCount) {
        throw ecs::error::ComponentError("Animation", fmt::format("Cannot use the animation {} because only have {} animations", animationId, this->animationsCount));
    }
    auto& animation = (background ? this->backgroundAnimations : this->topLevelAnimations);
    animation.noLoop = true;
    animation.noLoopToId = animationId - 1;
    if (animation.usedAnimation == animation.noLoopToId) {
        animation.noLoop = false;
    }
}

void ecs::component::Animation::pause(bool pausing, bool background) noexcept
{
    (background ? this->backgroundAnimations : this->topLevelAnimations).paused = pausing;
}

void ecs::component::Animation::clear(bool waitingForCurrentEnd, bool background) noexcept
{
    auto& animation = (background ? this->backgroundAnimations : this->topLevelAnimations);
    std::queue<unsigned int>().swap(animation.animationsQueue);
    if (not waitingForCurrentEnd) {
        animation.running = false;
    }
}
