#include "pch.h"
#include "DayOne.h"

#include <Utilities/Input.h>

// System
#include <numeric>
#include <algorithm>
#include <assert.h>
#include <istream>
#include <iostream>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
namespace
{
    //------------------------------------------------------------------------------
    // Parsing
   // void ParseLine(std::string& line);
}

//------------------------------------------------------------------------------
namespace DayOne
{
    
    void Puzzle::DoPuzzle(std::istream& inData)
    {
        std::string line;

        std::vector<int> values;

        mHorde.NewElf();

        while (std::getline(inData, line))
        {
            if (!line.empty())
            {
                mHorde.AddCalories(stoi(line));
            }
            else
            {
                mHorde.NewElf();
            }
        }

        mHorde.Finish();
        
        SolvePuzzle();
    }

    void Puzzle::SolvePuzzle()
    {
        const unsigned int topCount = 3;
        const unsigned int maxCals = mHorde.GetMaxSum(1);
        const unsigned int maxThree = mHorde.GetMaxSum(topCount);

        std::cout << "Max Calories: " << maxCals << std::endl;
        std::cout << "Sum 3 Calories: " << maxThree << std::endl;
    }

    //------------------------------------------------------------------------------
    // Elf
    bool operator<(const Elf& lhs, const Elf& rhs) 
    { 
        return lhs.GetCalories() > rhs.GetCalories(); 
    }

    unsigned int ElfSum(unsigned int lhs, const Elf& rhs)
    {
        return lhs + rhs.GetCalories();
    }


    //------------------------------------------------------------------------------
    // Horde
    
    Horde::Horde()
    {
        mElfs.emplace_back();
    }

    void Horde::AddCalories(unsigned int cals)
    {
        assert(!mElfs.empty());
        mElfs.back().AddCalories(cals);
    }

    void Horde::NewElf()
    {
        mElfs.emplace_back();
    }

    void Horde::Finish()
    {
        std::sort(mElfs.begin(), mElfs.end());
        mSorted = true;
    }

    unsigned int Horde::GetMaxSum(unsigned int count) const
    {
        assert(count <= mElfs.size());
        assert(mSorted);

        const unsigned int calSum = std::accumulate(mElfs.begin(), mElfs.begin() + count, 0, ElfSum);
        return calSum;
    }


    void DoPartOne(const std::string& filename)
    {
        auto fileLines = Utilities::ReadAllLinesInFile(filename);
        std::vector<uint32_t> calories; 
        
        calories.push_back(0);
        auto currentElf = calories.end() - 1;

        for (const auto& line : fileLines)
        {
            (void)line;
        }
    }
    void DoPartTwo(const std::string& /*filename*/) {}
}