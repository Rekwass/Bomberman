/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Graphic Tests
*/

#include "Graphic/Window.hpp"

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(Graphic, CreateWindow)
{
    // NOLINTNEXTLINE
    EXPECT_NO_THROW(
        graphic::Window window("Bomberman", 60);
        window.setMaximized(););
}
