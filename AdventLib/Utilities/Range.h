#pragma once

class Range 
{
public:
    int32_t mStart;
    int32_t mEnd;

    // Overload the "less than" operator for sorting the ranges in the set
    bool operator<(const Range& other) const 
    {
        return mStart < other.mStart;
    }
};

class RangeSet
{
public:
    RangeSet() = default;
    void InsertRange(const Range& range);
    const std::set<Range>& GetRanges() const { return mRanges; }
private:
    std::set<Range> mRanges;
};

uint32_t CountUniqueValues(const std::set<Range>& ranges);