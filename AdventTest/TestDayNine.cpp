#include "pch.h"

// Advent Lib
#include <AdventDays/DayNine.h>

//------------------------------------------------------------------------------
// Test Helpers


TEST(DayNine, TestPartOneExamples)
{
    using namespace DayNine;

    RopeGrid ropeGrid;

    ropeGrid.MoveHead(GridDirection::Right, 4);
    EXPECT_EQ(ropeGrid.GetUniqueVisited(), 4);

    ropeGrid.MoveHead(GridDirection::Up, 4);

    EXPECT_EQ(ropeGrid.GetUniqueVisited(), 7);
    ropeGrid.MoveHead(GridDirection::Left, 3);

    EXPECT_EQ(ropeGrid.GetUniqueVisited(), 9);
    ropeGrid.MoveHead(GridDirection::Down, 1);

    EXPECT_EQ(ropeGrid.GetUniqueVisited(), 9);
    ropeGrid.MoveHead(GridDirection::Right, 4);

    ropeGrid.MoveHead(GridDirection::Down, 1);
    ropeGrid.MoveHead(GridDirection::Left, 5);
    ropeGrid.MoveHead(GridDirection::Right, 2);

    EXPECT_EQ(ropeGrid.GetUniqueVisited(), 13);
    
}
