#include "pch.h"
#include "StringUtils.h"

namespace Utilities
{
    std::vector<std::string> ReadAllLinesInFile(const std::filesystem::path& path)
    {
        std::vector<std::string> retLines;

        if (!std::filesystem::exists(path))
        {
            const std::string currentPath = std::filesystem::current_path().string();
            std::cout << "Could not open file at path: " << currentPath << path;
            return retLines;
        }

        {
            std::ifstream fileStream(path);
            std::string currentLine;

            while (std::getline(fileStream, currentLine))
            {
                retLines.emplace_back(currentLine);
            }
        }

        return retLines;
    }
    

    template<>
    std::vector<std::string> SplitString(const std::string& input, const std::string& delimiter)
    {
        return SplitStringAndTransform<std::string>(
            input,
            delimiter,
            [](const std::string& token) { return token; }); 
    }

    template<>
    std::vector<int32_t> SplitString(const std::string& input, const std::string& delimiter)
    {
        return SplitStringAndTransform<int32_t>(
            input,
            delimiter,
            [](const std::string& token) { return std::stoi(token); });
    }

    template<>
    std::vector<uint32_t> SplitString(const std::string& input, const std::string& delimiter)
    {
        return SplitStringAndTransform<uint32_t>(
            input,
            delimiter,
            [](const std::string& token) { return std::stoi(token); });
    }

    template<>
    std::vector<int64_t> SplitString(const std::string& input, const std::string& delimiter)
    {
        return SplitStringAndTransform<int64_t>(
            input,
            delimiter,
            [](const std::string& token) { return std::stoll(token); });
    }
}