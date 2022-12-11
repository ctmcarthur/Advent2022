#include "pch.h"
#include "AdventDay.h"

//------------------------------------------------------------------------------
AdventDay::AdventDay(DayId day, YearId year, std::pair<PuzzleFunc, PuzzleFunc> solutions)
    : mDay(day)
    , mYear(year)
    , mPartOneFunc(std::move(solutions.first))
    , mPartTwoFunc(std::move(solutions.second))
{
    mDays[year][day] = this;
}


PuzzleSolution AdventDay::DoPartOne(const std::filesystem::path& filename) const
{
    return mPartOneFunc(filename);
}

PuzzleSolution AdventDay::DoPartTwo(const std::filesystem::path& filename) const
{
    return mPartTwoFunc(filename);
}

//------------------------------------------------------------------------------
// Static
AdventYearCatalog AdventDay::mDays;  // NOLINT

const AdventDayCatalog* AdventDay::GetDaysForYear(YearId year)
{ 
    const auto findIter = mDays.find(year);

    if (findIter == mDays.end())
    {
        return nullptr;
    }

    return &(findIter->second);
}