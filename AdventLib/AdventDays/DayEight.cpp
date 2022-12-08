#include "pch.h"
#include "DayEight.h"

// AdventLib
#include <Utilities/StringUtils.h>

namespace DayEight
{
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        std::cout << "The Answer is: " << std::endl;
        return {};
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        std::cout << "The Answer is: " << std::endl;
        return {};
    }
}