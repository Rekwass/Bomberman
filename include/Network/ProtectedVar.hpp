/*
** EPITECH PROJECT, 2022
** include
** File description:
** PortectedVar
*/

#pragma once

#include <mutex>

namespace network {

/*
 * Multi thread protected variable with mutexes
 */
template <typename T>
class ProtectedVar {
   public:
    ProtectedVar() noexcept = default;
    explicit ProtectedVar(T defaultValue) noexcept :
        data(defaultValue) { }
    ProtectedVar(ProtectedVar const& other) noexcept = delete;
    ProtectedVar(ProtectedVar&& other) noexcept = delete;
    ~ProtectedVar() noexcept = default;

    ProtectedVar& operator=(ProtectedVar const& other) noexcept = delete;
    ProtectedVar& operator=(ProtectedVar&& other) noexcept = delete;

    /*
     * Read the var data
     *
     * Return the data
     */
    T read() noexcept
    {
        std::unique_lock<std::mutex> lock(this->mutex);

        return this->data;
    }
    /*
     * Write a data inside the var data
     *
     * No return value
     *
     * data -> The new data to write
     */
    void write(T data) noexcept
    {
        std::unique_lock<std::mutex> lock(this->mutex);

        this->data = data;
    }

   private:
    T data;
    std::mutex mutex;
};

} // namespace network
