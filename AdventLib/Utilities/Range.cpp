#include "pch.h"
#include "Range.h"

// Define a function for inserting a new range into the data structure
void RangeSet::InsertRange(const Range& range)
{
    Range newRange = range;
    
    // Check if the new range overlaps with any ranges in the set
    for (auto rangeIt = mRanges.begin(); rangeIt != mRanges.end();)
    {
        // Check if the current range overlaps with the new range
        if (rangeIt->mStart <= newRange.mEnd && rangeIt->mEnd >= newRange.mStart)
        {
            // Merge the current range with the new range
            newRange.mStart = std::min(rangeIt->mStart, newRange.mStart);
            newRange.mEnd = std::max(rangeIt->mEnd, newRange.mEnd);

            // Remove the current range from the set
            rangeIt = mRanges.erase(rangeIt);
        }
        else 
        {
            // Move to the next range in the set
            ++rangeIt;
        }
    }

    // Insert the new range into the set
    mRanges.insert(newRange);
}

uint32_t CountUniqueValues(const std::set<Range>& ranges)
{
    uint32_t count = 0;

    for (const auto& range : ranges)
    {
        count += range.mEnd - range.mStart + 1;
    }

    return count;
}