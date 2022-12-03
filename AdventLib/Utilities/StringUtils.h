#pragma once

namespace Utilities
{
    [[nodiscard]] std::vector<std::string> ReadAllLinesInFile(const std::filesystem::path& path);
  
    // Parses the input string into tokens separated by the provided delimiter and applies the supplied
    template<typename T>
    [[nodiscard]] std::vector<T> SplitStringAndTransform(
        const std::string& input,
        const std::string& delimiter,
        std::function<T(const std::string&)> transform)
    {
        std::vector<T> ret;
        for (const auto word : std::views::split(input, delimiter))
        {
            std::string newVal = std::string(word.begin(), word.end());
            ret.emplace_back(transform(newVal));
        }

        return ret;
    }

    template<typename T>
    [[nodiscard]] std::vector<T> SplitString(const std::string& input, const std::string& delimiter)
    {
        return Utilities::SplitStringAndTransform<T>(
            input,
            delimiter,
            [](const T& token) { return std::string(token); });
    }

    template<>
    [[nodiscard]] std::vector<std::string> SplitString(const std::string& input, const std::string& delimiter);

    template<>
    [[nodiscard]] std::vector<int32_t> SplitString(const std::string& input, const std::string& delimiter);

    template<>
    [[nodiscard]] std::vector<int64_t> SplitString(const std::string& input, const std::string& delimiter);

}