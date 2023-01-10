/*
** EPITECH PROJECT, 2022
** Indie-Studio
** File description:
** Vector
*/

#include "Vector.hpp"

utils::Vector utils::Vector::operator+(utils::Vector other) const noexcept
{
    return {this->x + other.x, this->y + other.y, this->z + other.z};
}

utils::Vector utils::Vector::operator+(float other) const noexcept
{
    return {this->x + other, this->y + other, this->z + other};
}

utils::Vector utils::Vector::operator-(utils::Vector other) const noexcept
{
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

utils::Vector utils::Vector::operator-(float other) const noexcept
{
    return {this->x - other, this->y - other, this->z - other};
}

utils::Vector utils::Vector::operator*(utils::Vector other) const noexcept
{
    return {this->x * other.x, this->y * other.y, this->z * other.z};
}

utils::Vector utils::Vector::operator*(float other) const noexcept
{
    return {this->x * other, this->y * other, this->z * other};
}

utils::Vector utils::Vector::operator/(utils::Vector other) const noexcept
{
    if (other.x == 0 or other.y == 0 or other.z == 0) {
        return *this;
    }
    return {this->x / other.x, this->y / other.y, this->z / other.z};
}

utils::Vector utils::Vector::operator/(float other) const noexcept
{
    if (other == 0) {
        return *this;
    }
    return {this->x / other, this->y / other, this->z / other};
}

utils::Vector& utils::Vector::operator++() noexcept
{
    this->x++;
    this->y++;
    this->z++;

    return *this;
}

utils::Vector& utils::Vector::operator--() noexcept
{
    this->x--;
    this->y--;
    this->z--;

    return *this;
}

bool utils::Vector::operator==(const Vector& other) const noexcept
{
    return (this->x == other.x and this->y == other.y and this->z == other.z);
}

bool utils::Vector::operator!=(utils::Vector const& other) const noexcept
{
    return (this->x != other.x or this->y != other.y or this->z != other.z);
}

bool utils::Vector::operator>(utils::Vector const& other) const noexcept
{
    return (this->x > other.x and this->y > other.y and this->z > other.z);
}

bool utils::Vector::operator<(utils::Vector const& other) const noexcept
{
    return (this->x < other.x and this->y < other.y and this->z < other.z);
}

bool utils::Vector::operator>=(utils::Vector const& other) const noexcept
{
    return (this->x >= other.x and this->y >= other.y and this->z >= other.z);
}

bool utils::Vector::operator<=(utils::Vector const& other) const noexcept
{
    return (this->x <= other.x and this->y <= other.y and this->z <= other.z);
}

bool utils::Vector::operator!() const noexcept
{
    return (this->x == 0 and this->y == 0 and this->z == 0);
}

utils::Vector& utils::Vector::operator+=(utils::Vector other) noexcept
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;

    return *this;
}

utils::Vector& utils::Vector::operator-=(utils::Vector other) noexcept
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;

    return *this;
}

utils::Vector& utils::Vector::operator*=(utils::Vector other) noexcept
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;

    return *this;
}

utils::Vector& utils::Vector::operator/=(Vector other) noexcept
{
    if (other.x == 0 or other.y == 0 or other.z == 0) {
        return *this;
    }
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;

    return *this;
}

utils::Vector::operator Vector3() const
{
    return {this->x, this->y, this->z};
}

std::size_t utils::VectorHash::operator()(const Vector& vector) const noexcept
{
    std::size_t h1 = std::hash<float>()(vector.x);
    std::size_t h2 = std::hash<float>()(vector.y);
    std::size_t h3 = std::hash<float>()(vector.z);

    return (h1 ^ h2 ^ h3);
}
