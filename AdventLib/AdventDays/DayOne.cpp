#include "pch.h"
#include "DayOne.h"

#include <Utilities/StringUtils.h>


//------------------------------------------------------------------------------
namespace DayOne
{
    //------------------------------------------------------------------------------
    // Helpers
    
    // sum of calories for each elf.
    using CalorieCount = std::vector<uint32_t>;

    //------------------------------------------------------------------------------
    unsigned int GetMaxSum(CalorieCount& calories, uint32_t count)
    {
        std::partial_sort(calories.begin(), calories.begin()+count, calories.end(), std::greater<>());
        const uint32_t calSum =
            std::accumulate(calories.begin(), calories.begin() + count, 0U);
        return calSum;
    }

    //------------------------------------------------------------------------------
    CalorieCount ParseCalories(const std::string& filename)
    {
        const auto fileLines = Utilities::ReadAllLinesInFile(filename);
        CalorieCount calories;

        calories.push_back(0);
        auto currentElf = calories.end() - 1;

        for (const auto& line : fileLines)
        {
            if (line.empty())
            {
                calories.push_back(0);
            }
            else
            {
                calories.back() += std::stoi(line);
            }
        }

        return calories;
    }

    //------------------------------------------------------------------------------
    // Part 1
    std::any DoPartOne(const std::string& filename)
    {        
        CalorieCount calories = ParseCalories(filename);
        const uint32_t maxCals = GetMaxSum(calories, 1);
        
        std::cout << "Elf With the Most Calories: " << maxCals << std::endl;
       
        return maxCals;
    }

    //------------------------------------------------------------------------------
    // Part 2
    std::any DoPartTwo(const std::string& filename) 
    { 
        CalorieCount calories = ParseCalories(filename);

        constexpr uint32_t topCount = 3;
        const uint32_t maxThree = GetMaxSum(calories, topCount);

        std::cout << "Calories carried by Top " << topCount << " elves: " 
            << maxThree << std::endl;

        return maxThree;
    }
}