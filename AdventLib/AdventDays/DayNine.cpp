#include "pch.h"
#include "DayNine.h"

// AdventLib
#include <Utilities/EnumArray.h>
#include <Utilities/Grid.h>
#include <Utilities/Hashing.h>
#include <Utilities/StringUtils.h>

namespace DayNine
{
    /*
      Tail can only be max of 1 unit distance behind.
      if X or Y is greater than Max units, then subtract 1 from it, then restore its sign (-2->-1,  2->1) on either axis.
    */

    bool PullTail(const GridCoordinate& headPos, GridCoordinate& tailPos);
    //------------------------------------------------------------------------------
    // Rope Grid
    RopeGrid::RopeGrid()
        : RopeGrid(2)
    {
    }


    constexpr GridCoordinate kStartLocation = { 0, 0 };
    RopeGrid::RopeGrid(size_t knotCount)
        : mKnots(knotCount, GridCoordinate{ kStartLocation })
    {
        mTailVisited.insert(kStartLocation);
    }

    void RopeGrid::MoveHead(GridDirection direction)
    {
        assert(mKnots.size() > 1);
        
        const auto tailKnot = std::prev(mKnots.end());


        auto currentKnot = mKnots.begin();

        (*currentKnot) = ShiftOnGrid(*currentKnot, direction);
        
        for (currentKnot; currentKnot != tailKnot; ++currentKnot)
        {
            PullTail(*currentKnot, *std::next(currentKnot));
        }
            
        RecordTail(*tailKnot);
        
    }

    void RopeGrid::MoveHead(GridDirection direction, int32_t repeat)
    {
        for (int32_t i = 0; i < repeat; ++i)
        {
            MoveHead(direction);
        }
    }

    //------------------------------------------------------------------------------
    bool ShouldMove(const GridOffset& absoluteDistance)
    {
        return absoluteDistance.dX > 1 || absoluteDistance.dY > 1;
    }
    
    //------------------------------------------------------------------------------
    GridOffset NormalizeOffset(const GridOffset& offset)
    {
        GridOffset normalized = { 0,0 };

        if (offset.dX)
        {
            if (offset.dX < 0)
            {
                normalized.dX = -1;
            }
            else
            {
                normalized.dX = 1;
            }
        }

        if (offset.dY)
        {
            if (offset.dY < 0)
            {
                normalized.dY = -1;
            }
            else
            {
                normalized.dY = 1;
            }
        }

        return normalized;
    }

//------------------------------------------------------------------------------
    bool PullTail(const GridCoordinate& headPos, GridCoordinate& tailPos)
    {
        const GridOffset distance = headPos.Distance(tailPos);
        const GridOffset absDistance = { std::abs(distance.dX), std::abs(distance.dY) };

        assert(absDistance.dX <= 2);
        assert(absDistance.dY <= 2);


        if (!ShouldMove(absDistance))
        {
            return false;
        }
      
        const GridOffset moveDirection = NormalizeOffset(distance);
        
        tailPos.x += moveDirection.dX;
        tailPos.y += moveDirection.dY;
     return true;
    }

    //------------------------------------------------------------------------------
    void RopeGrid::RecordTail(const GridCoordinate& tailPos)
    {
        mTailVisited.insert(tailPos);
    }

    //------------------------------------------------------------------------------
    static const std::unordered_map<char, GridDirection> kInputDirMap =
    {
        {'L', GridDirection::Left},
        {'R', GridDirection::Right},
        {'U', GridDirection::Up},
        {'D', GridDirection::Down}
    };

   
    //------------------------------------------------------------------------------
    // Parsing
    void ParseInput(const std::string& filename, RopeGrid& outRopeGrid)
    {
        static constexpr size_t kInputDirIdx = 0;
        static constexpr size_t kInputCountIdx = 2;

        const auto input = StringUtils::SplitFile(filename);
        for (const auto& line : input)
        {
            const char dirChar = line.at(kInputDirIdx);
            const uint32_t count = std::stoi(line.substr(kInputCountIdx));
            outRopeGrid.MoveHead(kInputDirMap.at(dirChar), count);
        }
    }
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        RopeGrid ropeGrid;
        ParseInput(filename, ropeGrid);

        const auto numVisited = ropeGrid.GetUniqueVisited();
        std::cout << "Number of Locations Visited is: " << numVisited << std::endl;

        return numVisited;
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        RopeGrid ropeGrid(10);
        ParseInput(filename, ropeGrid);

        const auto numVisited = ropeGrid.GetUniqueVisited();
        std::cout << "Number of Locations Visited by Tail is: " << numVisited << std::endl;

        return numVisited;
    }
}