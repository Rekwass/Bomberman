/*
** EPITECH PROJECT, 2022
** utils
** File description:
** Clock
*/

#include "Clock.hpp"

utils::Clock::Clock() noexcept { this->saveTimePoint(); }

void utils::Clock::saveTimePoint() noexcept
{
    this->timepoint = utils::Clock::getActualTime();
}

bool utils::Clock::isElapsed(int milliseconds) const noexcept
{
    time_t actualTime = getActualTime();

    return (this->timepoint + milliseconds <= actualTime);
}

float utils::Clock::getElapsedTime() const noexcept
{
    time_t actualTime = getActualTime();

    return actualTime - this->timepoint;
}

#if defined(windows)
int gettimeofday(struct timeval* tv, struct timezone* tz)
{
    static __int64 birthunixhnsec = 116444736000000000; /*in units of 100 ns */
    FILETIME systemtime;
    GetSystemTimeAsFileTime(&systemtime);

    ULARGE_INTEGER utime;
    utime.LowPart = systemtime.dwLowDateTime;
    utime.HighPart = systemtime.dwHighDateTime;

    ULARGE_INTEGER birthunix;
    birthunix.LowPart = (DWORD)birthunixhnsec;
    birthunix.HighPart = birthunixhnsec >> 32;

    LONGLONG usecs;
    usecs = (LONGLONG)((utime.QuadPart - birthunix.QuadPart) / 10);

    tv->tv_sec = (long)(usecs / 1000000);
    tv->tv_usec = (long)(usecs % 1000000);

    return 0;
}
#endif

time_t utils::Clock::getActualTime() noexcept
{
    struct timeval time_now {
    };

    gettimeofday(&time_now, nullptr);
    return ((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000));
}
