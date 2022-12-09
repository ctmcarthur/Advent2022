#include "pch.h"
#include "DayNine.h"

// AdventLib
#include <Utilities/StringUtils.h>

namespace DayNine
{
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        const auto input = StringUtils::SplitFile(filename);
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
        (void)filename;
        std::cout << "The Answer is: " << std::endl;
        return {};
    }
}