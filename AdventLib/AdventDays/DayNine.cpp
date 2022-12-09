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

  
    constexpr GridCoordinate kStartLocation = { 0, 0 };

    //------------------------------------------------------------------------------
    // Rope Grid
    RopeGrid::RopeGrid()
        : mHeadPos{kStartLocation}
        , mTailPos{kStartLocation}
    {
        mTailVisited.insert(0);
    }

    void RopeGrid::MoveHead(GridDirection direction)
    {
        mHeadPos = ShiftOnGrid(mHeadPos, direction);
        
        PullTail();
    }

    void RopeGrid::MoveHead(GridDirection direction, int32_t repeat)
    {
     //   std::cout << "Move dir: " << static_cast<uint16_t>(direction) << std::endl;
      //  std::cout << "=================" << std::endl;
        for (int32_t i = 0; i < repeat; ++i)
        {
            MoveHead(direction);
        }
    }

    void RopeGrid::PullTail()
    {
        const GridOffset distance = mHeadPos.Distance(mTailPos);
        const GridOffset absDistance = { std::abs(distance.first), std::abs(distance.second) };


      //  std::cout << "------------" << std::endl;
       // std::cout << "Head x: " << mHeadPos.x << " Head y: " << mHeadPos.y << std::endl;
       // std::cout << "Tail x: " << mTailPos.x << " Tail y: " << mTailPos.y << std::endl;


        assert(absDistance.first <= (mMaxDistance + 1));
        assert(absDistance.second <= (mMaxDistance + 1));


        GridOffset toMove;

        if (absDistance.first > mMaxDistance)
        {
            toMove.first = absDistance.first - mMaxDistance;
            toMove.second = absDistance.second;
        }
        else if (absDistance.second > mMaxDistance)
        {
            toMove.first = absDistance.first;
            toMove.second = absDistance.second - mMaxDistance;
        }
        else
        {
          //  std::cout << "toMove x: " <<0 << " toMove y: " <<0 << std::endl;
            return;
        }

        if (distance.first < 0)
        {
            toMove.first *= -1;
        }

        if (distance.second < 0)
        {
            toMove.second *= -1;
        }


        
      //  std::cout << "toMove x: " << toMove.first << " toMove y: " << toMove.second << std::endl;
        mTailPos = mTailPos + toMove;
        
        mTailVisited.insert((mTailPos.y*100000 + mTailPos.x));

      //  std::cout << "Unique Values " << mTailVisited.size() << std::endl;
    }
    
    static const std::unordered_map<char, GridDirection> kInputDirMap =
    {
        {'L', GridDirection::Left},
        {'R', GridDirection::Right},
        {'U', GridDirection::Up},
        {'D', GridDirection::Down}
    };

    static constexpr size_t kInputDirIdx = 0;
    static constexpr size_t kInputCountIdx = 2;
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        RopeGrid ropeGrid;

        const auto input = StringUtils::SplitFile(filename);
        for (const auto& line : input)
        {
            const char dirChar = line.at(kInputDirIdx);
            const char countChar = line.at(kInputCountIdx);
            ropeGrid.MoveHead(kInputDirMap.at(dirChar), std::stoi(std::string(1, countChar)));
        }

        const auto numVisited = ropeGrid.GetUniqueVisited();
        std::cout << "Number of Locations Visited is: " << numVisited << std::endl;

        return numVisited;
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        (void)filename;
        std::cout << "The Answer is: " << std::endl;
        return {};
    }
}