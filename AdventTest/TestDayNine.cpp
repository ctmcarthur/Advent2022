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

TEST(DayNine, TestRopeTailStationary)
{
    using namespace DayNine;

    // dont move
    {
        RopeGrid ropeGrid;
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }

    //Right
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{0,0}));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);

        // R twice
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
    }
}

TEST(DayNine, RopeMoveShortCardinal)
{
    using namespace DayNine;

    //Right
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }

    //Left
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Left);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }

    //Up
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }

    //Down
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }
}

TEST(DayNine, RopeMoveLongCardinal)
{
    using namespace DayNine;

    //Right
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 2,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 3);
    }
    //Left
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Left);
        ropeGrid.MoveHead(GridDirection::Left);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -1,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        ropeGrid.MoveHead(GridDirection::Left);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -2,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 3);
    }
    //Up
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Up);
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,-1 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,-2 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 3);
    }
    //Down
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Down);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,1 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,2 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 3);
    }
}

TEST(DayNine, RopeMoveShortDiagonal)
{
    using namespace DayNine;

    //Right/Up
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }

    // Right/Down
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Down);
        ropeGrid.MoveHead(GridDirection::Right);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }
    //LEft/Up
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Left);
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }
    //Left/Down
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Left);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }
}

TEST(DayNine, RopeMoveLongDiagonal)
{
    using namespace DayNine;

    {
        //Right/Up -> Right
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Right);
            ropeGrid.MoveHead(GridDirection::Up);
            ropeGrid.MoveHead(GridDirection::Right);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,-1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
        //Right/Up -> Up
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Right);
            ropeGrid.MoveHead(GridDirection::Up);
            ropeGrid.MoveHead(GridDirection::Up);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,-1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
    }

    {
        //Right/Down -> Right
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Right);
            ropeGrid.MoveHead(GridDirection::Down);
            ropeGrid.MoveHead(GridDirection::Right);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
        //Right/Down -> Down
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Right);
            ropeGrid.MoveHead(GridDirection::Down);
            ropeGrid.MoveHead(GridDirection::Down);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
    }

    {
        //Left/Up -> Left
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Left);
            ropeGrid.MoveHead(GridDirection::Up);
            ropeGrid.MoveHead(GridDirection::Left);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -1,-1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
        //Left/Up -> Up
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Left);
            ropeGrid.MoveHead(GridDirection::Up);
            ropeGrid.MoveHead(GridDirection::Up);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -1,-1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
    }

    {
        //Left/Down -> Left
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Left);
            ropeGrid.MoveHead(GridDirection::Down);
            ropeGrid.MoveHead(GridDirection::Left);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -1, 1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
        //Left/Down -> Down
        {
            RopeGrid ropeGrid;
            ropeGrid.MoveHead(GridDirection::Left);
            ropeGrid.MoveHead(GridDirection::Down);
            ropeGrid.MoveHead(GridDirection::Down);
            EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ -1,1 }));
            EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        }
    }
}

TEST(DayNine, RopeBacktrack)
{
    using namespace DayNine;
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Left);
        ropeGrid.MoveHead(GridDirection::Down);
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Left);
        ropeGrid.MoveHead(GridDirection::Up);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 0,0 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 1);
    }
}

TEST(DayNine, RopeLongContinuousDiagonal)
{
    using namespace DayNine;
    //Right/Down -> Down
    {
        RopeGrid ropeGrid;
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Down);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,1 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 2);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 1,2 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 3);
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 2,3 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 4);
        ropeGrid.MoveHead(GridDirection::Right);
        ropeGrid.MoveHead(GridDirection::Down);
        EXPECT_EQ(ropeGrid.GetTail(), (GridCoordinate{ 3,4 }));
        EXPECT_EQ(ropeGrid.GetUniqueVisited(), 5);
    }
}