/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Vector
*/

#include "Vector.hpp"

#include <gtest/gtest.h>

TEST(Vector, Addition)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    float value = 7.0;

    auto res = v1 + v2;
    EXPECT_EQ(res.x, v1.x + v2.x);
    EXPECT_EQ(res.y, v1.y + v2.y);
    EXPECT_EQ(res.z, v1.z + v2.z);

    auto res2 = v1 + value;
    EXPECT_EQ(res2.x, v1.x + value);
    EXPECT_EQ(res2.y, v1.y + value);
    EXPECT_EQ(res2.z, v1.z + value);
}

TEST(Vector, Substraction)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    float value = 7.0;

    auto res = v1 - v2;
    EXPECT_EQ(res.x, v1.x - v2.x);
    EXPECT_EQ(res.y, v1.y - v2.y);
    EXPECT_EQ(res.z, v1.z - v2.z);

    auto res2 = v1 - value;
    EXPECT_EQ(res2.x, v1.x - value);
    EXPECT_EQ(res2.y, v1.y - value);
    EXPECT_EQ(res2.z, v1.z - value);
}

TEST(Vector, Multiplication)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    float value = 7.0;

    auto res = v1 * v2;
    EXPECT_EQ(res.x, v1.x * v2.x);
    EXPECT_EQ(res.y, v1.y * v2.y);
    EXPECT_EQ(res.z, v1.z * v2.z);

    auto res2 = v1 * value;
    EXPECT_EQ(res2.x, v1.x * value);
    EXPECT_EQ(res2.y, v1.y * value);
    EXPECT_EQ(res2.z, v1.z * value);
}

TEST(Vector, Division)
{
    utils::Vector v1{10, 20, 30};
    utils::Vector v2{0, 0, 0};
    utils::Vector v3{2, 5, 6};
    float value = 5;
    float value2 = 0;

    auto res = v1 / v3;
    EXPECT_EQ(res.x, v1.x / v3.x);
    EXPECT_EQ(res.y, v1.y / v3.y);
    EXPECT_EQ(res.z, v1.z / v3.z);

    auto res2 = v1 / v2;
    EXPECT_EQ(res2.x, v1.x);
    EXPECT_EQ(res2.y, v1.y);
    EXPECT_EQ(res2.z, v1.z);

    auto res3 = v1 / value;
    EXPECT_EQ(res3.x, v1.x / value);
    EXPECT_EQ(res3.y, v1.y / value);
    EXPECT_EQ(res3.z, v1.z / value);

    auto res4 = v3 / value2;
    EXPECT_EQ(res4.x, v3.x);
    EXPECT_EQ(res4.y, v3.y);
    EXPECT_EQ(res4.z, v3.z);
}

TEST(Vector, Equality)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{1, 2, 3};
    utils::Vector v3{4, 5, 6};

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(Vector, Inequality)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{1, 2, 3};
    utils::Vector v3{4, 5, 6};

    EXPECT_FALSE(v1 != v2);
    EXPECT_TRUE(v1 != v3);
}

TEST(Vector, Superior)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector v3{7, 8, 9};

    EXPECT_TRUE(v2 > v1);
    EXPECT_FALSE(v2 > v3);
}

TEST(Vector, Inferior)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector v3{7, 8, 9};

    EXPECT_FALSE(v2 < v1);
    EXPECT_TRUE(v2 < v3);
}

TEST(Vector, SuperiorOrEqual)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector v3{4, 5, 6};
    utils::Vector v4{7, 8, 9};

    EXPECT_TRUE(v3 >= v1);
    EXPECT_TRUE(v3 >= v2);
    EXPECT_FALSE(v3 >= v4);
}

TEST(Vector, InferiorOrEqual)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector v3{4, 5, 6};
    utils::Vector v4{7, 8, 9};

    EXPECT_FALSE(v3 <= v1);
    EXPECT_TRUE(v3 <= v2);
    EXPECT_TRUE(v3 <= v4);
}

TEST(Vector, Nullable)
{
    utils::Vector v1{0, 0, 0};
    utils::Vector v2{1, 2, 3};

    EXPECT_TRUE(!v1);
    EXPECT_FALSE(!v2);
}

TEST(Vector, AdditionRef)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector copy = v1;

    v1 += v2;
    EXPECT_EQ(v1.x, copy.x + v2.x);
    EXPECT_EQ(v1.y, copy.y + v2.y);
    EXPECT_EQ(v1.z, copy.z + v2.z);
}

TEST(Vector, SubstractionRef)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector copy = v1;

    v1 -= v2;
    EXPECT_EQ(v1.x, copy.x - v2.x);
    EXPECT_EQ(v1.y, copy.y - v2.y);
    EXPECT_EQ(v1.z, copy.z - v2.z);
}

TEST(Vector, MultiplicationRef)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector copy = v1;

    v1 *= v2;
    EXPECT_EQ(v1.x, copy.x * v2.x);
    EXPECT_EQ(v1.y, copy.y * v2.y);
    EXPECT_EQ(v1.z, copy.z * v2.z);
}

TEST(Vector, DivisionRef)
{
    utils::Vector v1{1, 2, 3};
    utils::Vector v2{4, 5, 6};
    utils::Vector v3{0, 0, 0};
    utils::Vector copy = v1;

    v1 /= v2;
    EXPECT_EQ(v1.x, copy.x / v2.x);
    EXPECT_EQ(v1.y, copy.y / v2.y);
    EXPECT_EQ(v1.z, copy.z / v2.z);

    v1 /= v3;
    EXPECT_EQ(v1.x, v1.x);
    EXPECT_EQ(v1.y, v1.y);
    EXPECT_EQ(v1.z, v1.z);
}

TEST(Vector, Parantheses)
{
    float x = 1;
    float y = 2;
    float z = 3;

    auto res = Vector3{x, y, z};
    EXPECT_EQ(res.x, x);
    EXPECT_EQ(res.y, y);
    EXPECT_EQ(res.z, z);
}
