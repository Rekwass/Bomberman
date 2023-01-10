/*
** EPITECH PROJECT, 2022
** include
** File description:
** Randomizer
*/

#pragma once

#include <cstddef>
#include <functional>
#include <random>
#include <unordered_map>

namespace utils {

template <typename T>
struct MinMax {
    bool operator==(const MinMax& other) const noexcept
    {
        return (this->min == other.min and this->max == other.max);
    }
    T min = 0;
    T max = 0;
};

struct MinMaxHash {
    template <class T>
    std::size_t operator()(const MinMax<T>& obj) const noexcept
    {
        std::size_t h1 = std::hash<T>()(obj.min);
        std::size_t h2 = std::hash<T>()(obj.max);

        return h1 ^ h2;
    }
};

/*
 * Generate a random number in a given range
 */
class Randomizer {
   public:
    Randomizer() noexcept = delete;
    Randomizer(Randomizer const& other) noexcept = delete;
    Randomizer(Randomizer&& other) noexcept = delete;
    ~Randomizer() noexcept = delete;

    Randomizer& operator=(Randomizer const& other) noexcept = delete;
    Randomizer& operator=(Randomizer&& other) noexcept = delete;

    /*
     * Return a random number generated between the two given numbers (included)
     */
    template <typename T = int>
    static T getRandomNumber(T min, T max) noexcept
    {
        static std::random_device rd;
        static std::mt19937 mt(rd());
        static std::unordered_map<MinMax<T>, std::uniform_int_distribution<T>, MinMaxHash> map;

        if (not map.contains({min, max})) {
            map.insert({{min, max}, std::uniform_int_distribution<T>(min, max)});
        }
        return map.at({min, max})(mt);
    }
};

} // namespace utils
