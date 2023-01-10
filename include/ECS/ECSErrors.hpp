/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** ECSErrors
*/

#pragma once

#include <exception>
#include <string>

namespace ecs::error {

/*
 * ECS error thrown when an error occurred
 */
class ECSError : public std::exception {
   public:
    ECSError() noexcept = delete;
    explicit ECSError(std::string const& message);
    ECSError(ECSError const& other) = delete;
    ECSError(ECSError&& other) = delete;
    ~ECSError() override = default;

    ECSError& operator=(ECSError const& other) = delete;
    ECSError& operator=(ECSError&& other) = delete;

    /*
     * Return the error message
     */
    const char* what() const noexcept final;

   protected:
    /*
     * Message that describe the error
     */
    std::string message;
};

/*
 * ECS error thrown when an error occurred in a component
 */
class ComponentError final : public ECSError {
   public:
    explicit ComponentError(std::string const& name, std::string const& message);
    ComponentError(ComponentError const& other) = delete;
    ComponentError(ComponentError&& other) = delete;
    ~ComponentError() override = default;

    ComponentError& operator=(ComponentError const& other) = delete;
    ComponentError& operator=(ComponentError&& other) = delete;

    /*
     * Return a string that represent the component
     */
    const char* which() const noexcept;

   protected:
    /*
     * String that represent the component
     */
    std::string name;
};

} // namespace ecs::error
