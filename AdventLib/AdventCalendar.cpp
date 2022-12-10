#include "pch.h"
#include "AdventCalendar.h"

#include <AdventLib.h>

// System
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <sstream>

//------------------------------------------------------------------------------
// local decl
namespace
{
    template<class T>
    bool HasOption(std::initializer_list<T> options, T option)
    {
        return std::find(std::begin(options), std::end(options), option) != std::end(options);
    }

    std::string GetInputFilename(DayId day, PuzzleInputType dataSrc);
    void PrintSolution(PuzzleSection section, AdventDay& day, const std::string& filename);
}

//------------------------------------------------------------------------------
// AdventCalender definition
AdventCalendar::AdventCalendar(YearId year) 
    : mYear(year) 
{
    Year2022::RegisterDays();
}

//------------------------------------------------------------------------------
void AdventCalendar::DoToday() const
{
    const auto *const dayCatalog = AdventDay::GetDaysForYear(mYear);

    assert(dayCatalog != nullptr);

   
    const DayId today = std::prev(dayCatalog->end())->first;;

   // const PuzzleInputType dataSrc = PuzzleInputType::ExampleData;
    const PuzzleSectionFlags sections = { PuzzleSection::PartOne, PuzzleSection::PartTwo };

    std::cout << "**ExampleData**" << std::endl;
    DoDay(today, sections, PuzzleInputType::ExampleData);
    std::cout << std::endl << "**RealData**" << std::endl;
    DoDay(today, sections, PuzzleInputType::RealData);
}

//------------------------------------------------------------------------------
void AdventCalendar::DoDay(DayId day, PuzzleSectionFlags sections, PuzzleInputType dataSrc) const
{
    const auto* const dayCatalog = AdventDay::GetDaysForYear(mYear);
    assert(dayCatalog != nullptr);

    const auto findIter = dayCatalog->find(day);

    if (findIter == dayCatalog->end())
    {
        std::cout << "Can't find day: " << day << std::endl;
        return;
    }

    AdventDay& adventDay = *(findIter->second);

    const std::string fileName = GetInputFilename(day, dataSrc);

    std::cout << "=========================================================================" << std::endl;
    std::cout << "Day " << day << std::endl;
    std::cout << "=========================================================================" << std::endl;


    if (HasOption(sections, PuzzleSection::PartOne))
    {
        PrintSolution(PuzzleSection::PartOne, adventDay, fileName);
    }  

    if (HasOption(sections, PuzzleSection::PartTwo))
    {
        PrintSolution(PuzzleSection::PartTwo, adventDay, fileName);
    }
}

PuzzleSolution AdventCalendar::GetAnswer(DayId day, PuzzleSection section, PuzzleInputType dataSrc) const
{
    const auto* const dayCatalog = AdventDay::GetDaysForYear(mYear);
    assert(dayCatalog != nullptr);

    const auto findIter = dayCatalog->find(day);

    if (findIter == dayCatalog->end())
    {
        std::cout << "Can't find day: " << day << std::endl;
        return {};
    }

    AdventDay& adventDay = *(findIter->second);
    const std::string fileName = GetInputFilename(day, dataSrc);

    if (section == PuzzleSection::PartOne)
    {
        return adventDay.DoPartOne(fileName);
    }
   
    return adventDay.DoPartTwo(fileName); 
}

//------------------------------------------------------------------------------
void AdventCalendar::DoEveryDay(PuzzleSectionFlags sections, PuzzleInputType dataSrc) const
{
    const auto* const dayCatalog = AdventDay::GetDaysForYear(mYear);
    assert(dayCatalog != nullptr);

    for (const auto& [day, adventDay] : (*dayCatalog))
    {
        DoDay(day, sections, dataSrc);
    }
}

//------------------------------------------------------------------------------
// local definitions
namespace
{
    std::ostream& operator<< (std::ostream& out, PuzzleInputType dataSrc)
    {
        switch (dataSrc)
        {
        case PuzzleInputType::ExampleData:
            out << "Example"; 
            break;

        case PuzzleInputType::RealData: 
            out << "Input"; 
            break;
        }
        return out;
    }

    //------------------------------------------------------------------------------
    std::string GetInputFilename(DayId day, PuzzleInputType dataSrc)
    {
        constexpr std::string_view kFileNamePrefix = { R"(..\Data\Day)" };
        constexpr std::string_view kFileExtension = {R"(.txt)"};

        std::stringstream fileName;
        fileName << kFileNamePrefix << day << dataSrc << kFileExtension;
        return fileName.str();
    }

    //------------------------------------------------------------------------------
    void PrintSolution(PuzzleSection section, AdventDay& day, const std::string& filename)
    {
        // Part 1
        std::cout << "Part: " << static_cast<std::underlying_type<PuzzleSection>::type>(section) << std::endl;
        const auto start = std::chrono::high_resolution_clock::now();
       
        // print solution
        if (section == PuzzleSection::PartOne)
        {
            day.DoPartOne(filename);
        }
        else
        {
            day.DoPartTwo(filename);
        }

        const auto stop = std::chrono::high_resolution_clock::now();
        const auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        
        // Solved in XXms
        std::cout << std::endl << "Solved in " << durationMs.count() << " ms." << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
    }
}