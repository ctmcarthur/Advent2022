#pragma once

// System
#include <any>
#include <cstdint>
#include <fstream>
#include <functional>
#include <map>

//------------------------------------------------------------------------------
// Fwd Decls
class AdventDay;
class PuzzleSolution;

//------------------------------------------------------------------------------
// Types
using DayId = uint32_t;
using YearId = uint32_t;
using AdventDayCatalog = std::map<DayId, AdventDay*>; // replace with gsl__notnull;
using AdventYearCatalog = std::map <YearId, AdventDayCatalog>;

using PuzzleFunc = std::function<PuzzleSolution(const std::filesystem::path& filename)>;

//------------------------------------------------------------------------------
// Advent Day
class AdventDay
{
public:
    AdventDay(DayId day, YearId year, std::pair<PuzzleFunc, PuzzleFunc> solutions);
    
    YearId GetYear() const { return mYear; }
    DayId GetDay() const { return mDay; }

    PuzzleSolution DoPartOne(const std::filesystem::path& filename) const;
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename) const;

    // static helpers
    static const AdventYearCatalog& GetFullCatalog() { return mDays; }
    static const AdventDayCatalog* GetDaysForYear(YearId year);

private:
    DayId mDay;
    YearId mYear;

    PuzzleFunc mPartOneFunc;
    PuzzleFunc mPartTwoFunc;
    
    // static data
    static AdventYearCatalog mDays;
};

//------------------------------------------------------------------------------
// Puzzle Solution
class PuzzleSolution
{
public:
    using CompareFunc = std::function<bool(const std::any& lhs, const std::any& rhs)>;

    std::any mSolution;
    CompareFunc mCompareFunc;
};

//------------------------------------------------------------------------------
// Helper Function
template<typename T>
bool CompareAny(const std::any& lhs, const std::any& rhs)
{
    assert(lhs.type() == typeid(T));
    assert(rhs.type() == typeid(T));

    return std::any_cast<T>(lhs) == std::any_cast<T>(rhs);
}