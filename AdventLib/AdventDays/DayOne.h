#pragma once

#include <istream>
#include <vector>

namespace DayOne
{
    class Elf
    {
    public:
        unsigned int AddCalories(unsigned int cals) 
        {
            mCalories += cals; 
            return mCalories;
        }

        unsigned int GetCalories() const { return mCalories; }
        
    private:
        unsigned int mCalories = 0;
    };

    //------------------------------------------------------------------------------
    class Horde
    {
    public:
        Horde();
        void AddCalories(unsigned int cals);
        void NewElf();
        void Finish();
        unsigned int GetMaxSum(unsigned int count) const;

    private:
        std::vector<Elf> mElfs;
        bool mSorted = false;
    };

    class Puzzle
    {
    public:
        void DoPuzzle(std::istream& inData);

    private:
        void SolvePuzzle();
        Horde mHorde;
    };

}