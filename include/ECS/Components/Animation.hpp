/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Animation
*/

#pragma once

#include <queue>
#include <raylib.h>
#include <set>
#include <string_view>

namespace ecs::component {

/*
 * Animation component
 */
class Animation {
   public:
    Animation() noexcept = default;
    Animation(std::string_view animationFilePath, unsigned int animationsCount, int fps = 60);
    Animation(Animation const& other) noexcept = default;
    Animation(Animation&& other) noexcept;
    ~Animation() noexcept;

    Animation& operator=(Animation const& other) noexcept = default;
    Animation& operator=(Animation&& other) noexcept;

    /*
     * Set a new animations
     *
     * No return value
     *
     * animationFilePath -> The path of the animation .iqm file
     *
     * animationsCount -> Number of animations the file contain
     *
     * fps -> The fps of the animations
     */
    void setAnimations(std::string_view animationFilePath, unsigned int animationsCount, int fps = 60);
    /*
     * Get the number of animations
     *
     * Return the number of animations
     */
    int getAnimationsNumber() const noexcept;
    /*
     * Start an animation
     *
     * No return value
     *
     * animationIndex -> Index that represents an animation
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    void addAnimation(unsigned int animationId, bool background = true);
    /*
     * Update the animation
     *
     * No return value
     *
     * model -> The model on which do the animation
     *
     * elapsedTime -> The time since we want to update the animation (in seconds)
     *
     * NOTE: This function should be called by the ECS only
     */
    void update(const Model& model, float elapsedTime);
    /*
     * Check if the animation is ended
     *
     * Return true if the animation is ended and false otherwise
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    bool isEnded(bool background = true) const noexcept;
    /*
     * Set if the current animation should loop
     *
     * No return value
     *
     * looping -> Set to true if the animation should loop, false otherwise
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    void loop(unsigned int animationId, bool looping = true, bool background = true);
    /*
     * Disable all looped animations until the given animation
     *
     * No return value
     *
     * animationId -> The id that represent the animation it should go to
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    void noLoopTo(unsigned int animationId, bool background = true);
    /*
     * Pause the animation (or resume if false)
     *
     * No return value
     *
     * pausing = true -> Set to true if the animation should be paused and false if it should be resumed
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    void pause(bool pausing = true, bool background = true) noexcept;
    /*
     * Clear all the animations
     *
     * No return value
     *
     * waitingForCurrentEnd -> Set to true if the current running animation should be waiting to end
     *
     * background -> Set to true if the animation should be played on background
     *
     * That means that the not background animations will be played in priority
     */
    void clear(bool waitingForCurrentEnd = false, bool background = true) noexcept;

   private:
    struct AnimationDetails {
        bool running = false;
        bool paused = false;
        bool noLoop = false;
        unsigned int noLoopToId = 0;
        std::set<unsigned int> loopedAnimations{};
        std::queue<unsigned int> animationsQueue{};
        unsigned int usedAnimation = 0;
        float animationFrameCounter = 0;
    };

    /*
     * Start an animation if any should be started
     *
     * No return value
     */
    void startAnimations() noexcept;
    /*
     * End the current animation and pass to the next one if any
     *
     * No return value
     *
     * model -> The model on which do the animation
     */
    void endAnimation(const Model& model);

    bool valid = false;
    bool hasPriorityAnimations = false;
    AnimationDetails backgroundAnimations;
    AnimationDetails topLevelAnimations;
    ModelAnimation* animations = nullptr;
    unsigned int animationsCount = 0;
    int fps = 0;
};

} // namespace ecs::component
