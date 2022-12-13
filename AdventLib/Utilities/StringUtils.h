#pragma once
// borrowed without permission from MarcusReid https://github.com/RiotNu/advent-of-code-2022/blob/main/AdventOfCode/StringUtils/Input.h
namespace StringUtils
{
    //------------------------------------------------------------------------------
    [[nodiscard]] std::vector<std::string> SplitFile(const std::filesystem::path& path);
  
    //------------------------------------------------------------------------------
    // Parses the input string into tokens, then transforms each token
    template<typename T>
    [[nodiscard]] std::vector<T> SplitTransformString(
        const std::string& input,
        const std::string& delimiter,
        std::function<T(const std::string&)> transform)
    {
        std::vector<T> ret;
        for (const auto& word : std::views::split(input, delimiter))
        {
            std::string newVal = std::string(word.begin(), word.end());

            if (!newVal.empty())
            {
                ret.emplace_back(transform(newVal));
            }
        }

        return ret;
    }

    //------------------------------------------------------------------------------
    // Helper Function, that tries to automatically convert string to type using custom transforms.
    template<typename T>
    [[nodiscard]] std::vector<T> SplitString(const std::string& input, const std::string& delimiter)
    {
        return StringUtils::SplitTransformString<T>(
            input,
            delimiter,
            [](const T& token) { return std::string(token); });
    }

    //------------------------------------------------------------------------------
    // Transform implementations for different types.
    template<>
    [[nodiscard]] std::vector<std::string> SplitString(const std::string& input, const std::string& delimiter);

    template<>
    [[nodiscard]] std::vector<int32_t> SplitString(const std::string& input, const std::string& delimiter);

    template<>
    [[nodiscard]] std::vector<int64_t> SplitString(const std::string& input, const std::string& delimiter);

    template<>
    [[nodiscard]] std::vector<uint32_t> SplitString(const std::string& input, const std::string& delimiter);


}