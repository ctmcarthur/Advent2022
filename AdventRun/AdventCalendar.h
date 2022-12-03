#pragma once

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

//------------------------------------------------------------------------------
using DayId = uint32_t;

//------------------------------------------------------------------------------
class AdventDay
{
public:
    using PuzzleFunc = std::function<std::any(const std::string&)>;

    PuzzleFunc mDayOne;
    PuzzleFunc mDayTwo;
};

//------------------------------------------------------------------------------
class AdventCalendar
{
public:
    AdventCalendar();
    void DoToday(); 

    using PuzzleSectionFlags = std::initializer_list<PuzzleSection>;

    void DoDay(DayId day, PuzzleSectionFlags sections, PuzzleInputType dataSrc);
    void DoEveryDay(PuzzleSectionFlags sections, PuzzleInputType dataSrc);

private:
    std::map<DayId, AdventDay> mDays;
};