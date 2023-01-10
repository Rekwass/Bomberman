/*
** EPITECH PROJECT, 2022
** IndieStudio
** File description:
** FileReader
*/

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace utils {

/*
 * FileReader error thrown when an error occurred
 */
class FileReaderError : public std::exception {
   public:
    FileReaderError() noexcept = delete;
    explicit FileReaderError(std::string const& message);
    FileReaderError(FileReaderError const& other) = default;
    FileReaderError(FileReaderError&& other) = default;
    ~FileReaderError() override = default;

    FileReaderError& operator=(FileReaderError const& other) = default;
    FileReaderError& operator=(FileReaderError&& other) = default;

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

class FileReader {
   public:
    FileReader() noexcept = default;
    FileReader(FileReader const& other) noexcept = delete;
    FileReader(FileReader&& other) noexcept = delete;
    ~FileReader() noexcept = default;

    FileReader& operator=(FileReader const& other) noexcept = delete;
    FileReader& operator=(FileReader&& other) noexcept = delete;

    /*
     * Get the content from a file at the given path
     *
     * Return a std::string with the file content
     *
     * filePath -> the file path
     */
    static std::string GetContentFromFile(std::string_view filePath);

   private:
};

} // namespace utils
