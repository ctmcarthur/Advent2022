#pragma once

// system
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
    using PuzzleFunc = std::function<void(const std::string&)>;

    PuzzleFunc mDayOne;
    PuzzleFunc mDayTwo;
};

//------------------------------------------------------------------------------
class AdventCalendar
{
public:
    AdventCalendar();
    void DoToday(); 
    void DoDay(DayId day, std::initializer_list<PuzzleSection> sections, PuzzleInputType dataSrc);
    void DoEveryDay(std::initializer_list<PuzzleSection> sections, PuzzleInputType dataSrc);

private:
    std::map<DayId, AdventDay> mDays;
};