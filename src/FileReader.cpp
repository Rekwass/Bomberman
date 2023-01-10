/*
** EPITECH PROJECT, 2022
** src
** File description:
** FileReader
*/

#include "FileReader.hpp"

#include "fmt/core.h"

#include <fstream>

utils::FileReaderError::FileReaderError(std::string const& message) :
    message(message) { }

const char* utils::FileReaderError::what() const noexcept
{
    return this->message.c_str();
}

std::string utils::FileReader::GetContentFromFile(std::string_view filePath)
{
    std::ifstream inputFile(filePath.data());

    if (not inputFile.is_open()) {
        throw FileReaderError(fmt::format("Error: Could not open the following file '{}'.", filePath));
    }
    return std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
}
