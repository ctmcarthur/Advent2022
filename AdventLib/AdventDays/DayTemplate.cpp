#include "pch.h"
#include "DayX.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/StringUtils.h>

namespace DayX2022
{
    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        (void)input;

        const uint32_t retVal = 0;

        std::cout << "The Answer Is: " << retVal << "\n";

        return { {retVal}, {&CompareAny<uint32_t>} };

    }

    //------------------------------------------------------------------------------
    // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        (void)input;

        const uint32_t retVal = 0;

        std::cout << "The Answer Is: " << retVal << "\n";

        return { {retVal}, {&CompareAny<uint32_t>} };

    }
}