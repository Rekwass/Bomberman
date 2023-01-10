/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** EventsManager
*/

#pragma once

#include "ECS/Core/Events.hpp"

#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace ecs {

/*
 * Manage events listeners and detectors
 */
class EventsManager {
   public:
    EventsManager() noexcept = default;
    EventsManager(EventsManager const& other) noexcept = default;
    EventsManager(EventsManager&& other) noexcept = default;
    ~EventsManager() noexcept = default;

    EventsManager& operator=(EventsManager const& other) noexcept = default;
    EventsManager& operator=(EventsManager&& other) noexcept = default;

    /*
     * Call all listeners functions associated to the given event
     *
     * No return value
     *
     * event -> The event to call associated listeners
     */
    void sendEvent(const Events& event) const noexcept;
    /*
     * Add a listener function to call when the given event occurred
     *
     * No return value
     *
     * event -> The event the listener will be associated with
     *
     * f -> The function to call
     *
     * args -> The arguments to pass to the function
     */
    template <typename F, typename... Args>
    void addListener(const Events& event, F&& f, Args&&... args) noexcept
    {
        if (not this->listeners.contains(event)) {
            std::vector<std::unique_ptr<IListener>> vec;

            vec.emplace_back(std::make_unique<Listener<F, Args...>>(
                std::forward<F>(f), std::forward<Args>(args)...));

            this->listeners.insert({event, std::move(vec)});
        } else {
            this->listeners.at(event).push_back(
                std::make_unique<Listener<F, Args...>>(
                    std::forward<F>(f), std::forward<Args>(args)...));
        }
    }
    void removeListeners(const Events& event) noexcept;

   private:
    /*
     * Events listener interface
     */
    class IListener {
       public:
        IListener() noexcept = default;
        IListener(IListener const& other) noexcept = default;
        IListener(IListener&& other) noexcept = default;
        virtual ~IListener() noexcept = default;

        IListener& operator=(IListener const& other) noexcept = default;
        IListener& operator=(IListener&& other) noexcept = default;
        virtual void operator()() = 0;
    };
    /*
     * Events listener class
     */
    template <typename F, typename... Args>
    class Listener final : public IListener {
       public:
        Listener() noexcept = delete;
        explicit Listener(F&& f, Args&&... args) :
            f(std::forward<F>(f)), args(std::forward<Args>(args)...) { }
        Listener(Listener const& other) noexcept = default;
        Listener(Listener&& other) noexcept = default;
        ~Listener() noexcept final = default;

        Listener& operator=(Listener const& other) noexcept = default;
        Listener& operator=(Listener&& other) noexcept = default;
        void operator()() final { std::apply(this->f, std::move(this->args)); }

       private:
        F f;
        std::tuple<Args...> args;
    };
    std::unordered_map<Events, std::vector<std::unique_ptr<IListener>>> listeners;
};

} // namespace ecs
