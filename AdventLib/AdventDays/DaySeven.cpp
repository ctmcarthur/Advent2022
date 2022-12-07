#include "pch.h"
#include "DaySeven.h"

// AdventLib
#include <Utilities/StringUtils.h>

namespace DaySeven
{
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        uint32_t ret = 0;

        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        return ret;
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        uint32_t ret = 0;

        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        return ret;
    }
}