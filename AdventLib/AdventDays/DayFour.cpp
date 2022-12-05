#include "pch.h"

#include <Utilities/StringUtils.h>

namespace DayFour
{
    //------------------------------------------------------------------------------
    // Part One

    using CleanRange = std::pair<uint32_t, uint32_t>;

    bool IsOneSideSet(CleanRange lhs, CleanRange rhs)
    {
        return (lhs.first >= rhs.first)
            && (lhs.second <= rhs.second);
    }

    bool IsRangeASuperSet(CleanRange firstElf, CleanRange secondElf)
    {
        return IsOneSideSet(firstElf, secondElf) || IsOneSideSet(secondElf, firstElf);
    }

    CleanRange ParseRange(const std::string& inputLine)
    {
        static const std::string kIntsDelimeter("-");
        const auto elfRange = StringUtils::SplitString<uint32_t>(inputLine, kIntsDelimeter);
        assert(elfRange.size() == 2);

        return { elfRange.at(0), elfRange.at(1)};
    }

    std::pair<CleanRange, CleanRange> ParsePair(const std::string& inputLine)
    {
        static const std::string kPairDelimeter(",");

        const auto elfs = StringUtils::SplitString<std::string>(inputLine, kPairDelimeter);

        assert(elfs.size() == 2);

        return { ParseRange(elfs.at(0)), ParseRange(elfs.at(1)) };
    }

    //------------------------------------------------------------------------------
    // Do Part One
    std::any DoPartOne(const std::string& filename)
    {
        const auto input = StringUtils::SplitFile(filename);
        
        uint32_t superSetCount = 0;

        for (const auto& line : input)
        {
            auto cleanRanges = ParsePair(line);

            if (IsRangeASuperSet(cleanRanges.first, cleanRanges.second))
            {
                ++superSetCount;
            }
        }

        std::cout << "There are " << superSetCount << " Supersets!" << std::endl;

        return superSetCount;
    }


    //------------------------------------------------------------------------------
    // Part 2

    //------------------------------------------------------------------------------

    bool DoesOneSideOverlap(CleanRange lhs, CleanRange rhs)
    {
        if (lhs.first >= rhs.first &&
            lhs.first <= rhs.second)
        {
            return true;
        }

        if (lhs.second >= rhs.first &&
            lhs.second <= rhs.second)
        {
            return true;
        }

        return false;

    }
    bool DoRangesOverlap(CleanRange firstElf, CleanRange secondElf)
    {
        return DoesOneSideOverlap(firstElf, secondElf) || DoesOneSideOverlap(secondElf, firstElf);
    }

    //------------------------------------------------------------------------------
    std::any DoPartTwo(const std::string& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        uint32_t superSetCount = 0;

        for (const auto& line : input)
        {
            auto cleanRanges = ParsePair(line);

            if (DoRangesOverlap(cleanRanges.first, cleanRanges.second))
            {
                ++superSetCount;
            }
        }

        std::cout << "There are " << superSetCount << " Overlaps!" << std::endl;
        return superSetCount;
    }
}