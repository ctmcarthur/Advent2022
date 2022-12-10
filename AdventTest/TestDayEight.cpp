#include "pch.h"

// Advent Lib
#include <AdventDays/DayEight.h>
// system

//------------------------------------------------------------------------------
// Test Helpers

namespace
{

    void FillTestData(DayEight2022::Forest& forest)
    {
        forest.AddNextTree(3);
        forest.AddNextTree(0);
        forest.AddNextTree(3);
        forest.AddNextTree(7);
        forest.AddNextTree(3);

        forest.AddNextTree(2);
        forest.AddNextTree(5);
        forest.AddNextTree(5);
        forest.AddNextTree(1);
        forest.AddNextTree(2);

        forest.AddNextTree(6);
        forest.AddNextTree(5);
        forest.AddNextTree(3);
        forest.AddNextTree(3);
        forest.AddNextTree(2);

        forest.AddNextTree(3);
        forest.AddNextTree(3);
        forest.AddNextTree(5);
        forest.AddNextTree(4);
        forest.AddNextTree(9);

        forest.AddNextTree(3);
        forest.AddNextTree(5);
        forest.AddNextTree(3);
        forest.AddNextTree(9);
        forest.AddNextTree(0);

    }
}

TEST(DayEight, TestPartOneExamples) 
{
    using namespace DayEight2022;
    Forest forest({ 5, 5 }, Forest::Mode::CalcHeightsOnAdd);

    FillTestData(forest);
    EXPECT_EQ(forest.CountVisibleTrees(), 21u);
    
}

TEST(DayEight, TestPartTwoExamples)
{
    using namespace DayEight2022;
    Forest forest({ 5, 5 }, Forest::Mode::None);

    FillTestData(forest);
    EXPECT_EQ(forest.GetScenicScore(), 8u);

    // EXPECT_EQ(terminal.GetSumSize(100000), 95437);
}

