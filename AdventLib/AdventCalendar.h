#pragma once

// Advent Lib
#include <AdventDay.h>
// system
#include <any>
#include <cstdint>
#include <functional>
#include <string>
#include <map>

//------------------------------------------------------------------------------
enum class PuzzleSection : uint32_t 
{
    PartOne = 1,
    PartTwo = 2,
};

enum class PuzzleInputType : uint32_t
{
    ExampleData,
    RealData
};


constexpr YearId kCurrentYear = 2022; 

//------------------------------------------------------------------------------
class AdventCalendar
{
public:
    explicit AdventCalendar(YearId year = kCurrentYear);
    void DoToday() const; 

    using PuzzleSectionFlags = std::initializer_list<PuzzleSection>;

    void DoDay(DayId day, PuzzleSectionFlags sections, PuzzleInputType dataSrc) const;
    void DoEveryDay(PuzzleSectionFlags sections, PuzzleInputType dataSrc) const;

    PuzzleSolution GetAnswer(DayId day, PuzzleSection section, PuzzleInputType dataSrc) const;

private:
    YearId mYear;
};