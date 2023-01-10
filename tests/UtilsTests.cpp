/*
** EPITECH PROJECT, 2022
** Indie Studio
** File description:
** Utils Tests
*/

#include "Utils.hpp"

#include <gtest/gtest.h>

// NOLINTNEXTLINE
TEST(Utils, HowToUsePrinted)
{
    int ac = 2;
    const char* av[] = {"./bomberman", "-h", "NULL"};
    bool res = utils::checkUsage(ac, av);
    EXPECT_EQ(res, true);
}

// NOLINTNEXTLINE
TEST(Utils, HowToUsePrintedOther)
{
    int ac = 2;
    const char* av[] = {"./bomberman", "--help", "NULL"};
    bool res = utils::checkUsage(ac, av);
    EXPECT_EQ(res, true);
}

// NOLINTNEXTLINE
TEST(Utils, HowToUseNotPrinted)
{
    int ac = 2;
    const char* av[] = {"./bomberman", "file.json", "NULL"};
    bool res = utils::checkUsage(ac, av);
    EXPECT_EQ(res, false);
}

// NOLINTNEXTLINE
TEST(Utils, RaylibLogs)
{
    // NOLINTNEXTLINE
    EXPECT_NO_THROW(
        utils::setRaylibLogLevel(););
}

// NOLINTNEXTLINE
TEST(Utils, GetInsideBorder)
{
    int res = utils::getInsideBorder(30);
    EXPECT_EQ(res, 30);
}

// NOLINTNEXTLINE
TEST(Utils, GetInsideBorderNegative)
{
    int res = utils::getInsideBorder(-40);
    EXPECT_EQ(res, 320);
}
