/*
** EPITECH PROJECT, 2022
** Indie
** File description:
** Clock
*/

#pragma once

#include <chrono>

#if defined(_WIN32) or defined(_WIN64)
#define windows
#include "ClockWindows.hpp"
int gettimeofday(struct timeval* tv, struct timezone* tz);

#else
#include <sys/time.h>
#endif

namespace utils {

/*
 * Time management clock to use time based condition
 */
class Clock {
   public:
    Clock() noexcept;
    Clock(Clock const& other) noexcept = default;
    Clock(Clock&& other) noexcept = default;
    ~Clock() noexcept = default;

    Clock& operator=(Clock const& other) noexcept = default;
    Clock& operator=(Clock&& other) noexcept = default;

    /*
     * Save the actual time as a timepoint in the clock
     */
    void saveTimePoint() noexcept;
    /*
     * Return true if the given time (milliseconds) as been elapsed since the
     * last saved timepoint
     */
    bool isElapsed(int milliseconds) const noexcept;

    float getElapsedTime() const noexcept;

   private:
    /*
     * Get the actual time
     */
    static time_t getActualTime() noexcept;
    /*
     * Stock the last time
     */
    time_t timepoint{};
};

} // namespace utils
