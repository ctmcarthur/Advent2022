#pragma once

// system
#include <cstdint>
#include <functional>
#include <string>
#include <map>

//------------------------------------------------------------------------------
enum class SectionFlags : uint32_t 
{
    PartOne = 1 << 1,
    PartTwo = 1 << 2
};

enum class DataTypeFlags : uint8_t
{
    ExampleData = 1 << 1,
    RealData = 1 << 2
};

//------------------------------------------------------------------------------
using DayId = uint32_t;

//------------------------------------------------------------------------------
class AdventDay
{
public:
    using PuzzleFunc = void(const std::string&);
    std::function<PuzzleFunc> mDayOne;
    std::function<PuzzleFunc> mDayTwo;
};

//------------------------------------------------------------------------------
class AdventCalendar
{
public:
    AdventCalendar();
    void DoToday(); 
    void DoDay(DayId day, SectionFlags sections, DataTypeFlags dataSrc);
    void DoEveryDay(SectionFlags sections, DataTypeFlags dataSrc);

private:
    std::map<DayId, AdventDay> mDays;
};