#include "pch.h"
#include "DayEleven.h"
// adventLib
#include <AdventDay.h>
#include <Utilities/StringUtils.h>

namespace DayEleven2022
{
    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        uint32_t retVal = 0;

        std::cout << "Solution is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint32_t>} };
    }

    //------------------------------------------------------------------------------
    // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        uint32_t retVal = 0;

        std::cout << "Solution is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint32_t>} };
    }
}