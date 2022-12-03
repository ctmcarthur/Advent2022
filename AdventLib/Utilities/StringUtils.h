#pragma once
// stolen without permission from MarcusReid: 
// https://github.com/RiotNu/advent-of-code-2022/blob/main/AdventOfCode/Utilities/Input.h

namespace Utilities
{
    std::vector<std::string> ReadAllLinesInFile(const std::filesystem::path& path);
    std::vector<std::string> SplitString(const std::string& input, const std::string& delimiter);

  
    // Parses the input string into tokens separated by the provided delimiter and applies the supplied
    // transform to each token.
    template<typename T>
    std::vector<T> SplitStringAndTransform(
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
}