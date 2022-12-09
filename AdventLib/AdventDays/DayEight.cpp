#include "pch.h"
#include "DayEight.h"

// AdventLib
#include <Utilities/StringUtils.h>


/*
all trees on outside edge are visible.
a tree is interior visible if there are only trees shorter than it between it and an edge.
How many trees are visible at an edge.
*/

/*
Tree
-height
-MaxHeight in each direction
*/

/*
-- add a tree, set its height.
-- Recursively tell all its neighbors in a direction, my height.
-- If the height from that direction is a new high, recurse, otherwise quit. 
*/

// calculate
/*
for each tree, if my height is higher than all my max height neighbors, i am visible. 
*/
namespace DayEight
{
    constexpr std::array<std::pair<int16_t, int16_t>, static_cast<size_t>(Direction::COUNT)> kOffsets =
    { {
        {int16_t{-1}, int16_t{0}}, // Left
        {int16_t{1}, int16_t{0}}, // Right
        {int16_t{0}, int16_t{-1}}, // Up
        {int16_t{0}, int16_t{1}}  // Down
    } };

    //------------------------------------------------------------------------------
    ForestCoordinates operator+(const ForestCoordinates& lhs, const ForestCoordinates& rhs)
    {
        return { lhs.first + rhs.first,lhs.second + rhs.second };
    }

    //------------------------------------------------------------------------------
    Forest::Forest(const ForestCoordinates& dimensions, Mode mode)
        : mDimensions({ dimensions.first - 1, dimensions.second - 1 })
        , mMode(mode)
        , mGrid(dimensions.first, std::vector<Tree>(dimensions.second))
        
    {

       
    }

    //------------------------------------------------------------------------------
    uint32_t Forest::CountVisibleTrees() const
    {
        auto countVisible = static_cast<uint32_t>((mDimensions.first+1) * 2 + ((mDimensions.second-1) * 2)); // grab the edges as visible

        assert(mMode == Mode::CalcHeightsOnAdd);

        for (size_t i = 1; i < mDimensions.first; ++i)
        {
            for (size_t j = 1; j < mDimensions.second; ++j)
            {
                const Tree& currTree = mGrid[i][j];
                bool visible = false;

                for (auto neighborHeight : currTree.mMaxHeights)
                {
                    if (currTree.height > neighborHeight)
                    {
                        visible = true;
                        break;
                    }
                }

                if (visible)
                {
                    ++countVisible;
                }
            }
        }

        return countVisible;
    }

    //------------------------------------------------------------------------------
    uint32_t Forest::GetScenicScore() const
    {
        uint32_t maxScore = 0;


        for (size_t i = 1; i < mDimensions.first; ++i)
        {
            for (size_t j = 1; j < mDimensions.second; ++j)
            {
                uint32_t scenicScore = 1;
                const Tree& currTree = mGrid[i][j];

                //std::cout << std::endl << "Tree x: " << i << " y: " << j << " height: " << currTree.height << std::endl;
                for (uint16_t direction = 0; direction < static_cast<uint16_t>(Direction::COUNT); ++direction)
                {
                    const auto dirScenicScore = CalcScenicScore(ForestCoordinates{ i,j } + kOffsets.at(static_cast<size_t>(direction)),
                        currTree.height,
                        static_cast<Direction>(direction),
                        1);

                    assert(dirScenicScore > 0);
                   // std::cout << "Dir: " << direction << " score: " << dirScenicScore << std::endl;
                    scenicScore *= dirScenicScore;
                    
                }

                maxScore = std::max(scenicScore, maxScore);
            }
        }

        return maxScore;
    }

    //------------------------------------------------------------------------------
    uint32_t Forest::CalcScenicScore(ForestCoordinates pos, int16_t height, Direction checkDir, uint32_t jumps) const
    {
       
        assert(pos.first <= mDimensions.first);
        assert(pos.second <= mDimensions.second);

        const Tree& currTree = mGrid[pos.first][pos.second];
        
        if (height <= currTree.height)
        {
            return jumps;
        }

        const auto& offset = kOffsets.at(static_cast<size_t>(checkDir));

        // check bounds
        // since coordinates are unsigned need to check for wrapping first
        if (((offset.first < 0) && (pos.first == 0)) // left
            || ((offset.second < 0) && (pos.second == 0))) // up
        {
            return jumps;
        }
        ForestCoordinates newPos = pos + offset;

        if ((newPos.first > mDimensions.first)
            || (newPos.second > mDimensions.second))
        {
            return jumps;
        }

        return CalcScenicScore(newPos, height, checkDir, jumps + 1);
    }
  
    //------------------------------------------------------------------------------
    void Forest::AddNextTree(int16_t height)
    {
        AddTree(mCurrentPos, height);

        mCurrentPos = mCurrentPos + kOffsets[static_cast<size_t>(Direction::Right)];

        if (mCurrentPos.first > mDimensions.first)
        {
            mCurrentPos.first = 0;
            ++mCurrentPos.second;
        }
    }
    //------------------------------------------------------------------------------
    void Forest::AddTree(const ForestCoordinates& pos, int16_t height)
    {
        Tree& currTree = mGrid[pos.first][pos.second];
        currTree.height = height;
   

        if (mMode == Mode::CalcHeightsOnAdd)
        {
            SetMaxHeights(pos, height, Direction::Left);
            SetMaxHeights(pos, height, Direction::Right);
            SetMaxHeights(pos, height, Direction::Up);
            SetMaxHeights(pos, height, Direction::Down);
        }
    }

    //------------------------------------------------------------------------------
    void Forest::SetMaxHeights(const ForestCoordinates& pos, int16_t height, Direction travelDir)
    {
        if (!CheckEdgeDirectionAllowed(pos, travelDir))
        {
            return;
        }

        SetMaxHeightsRecurse(pos + kOffsets.at(static_cast<size_t>(travelDir)), height, travelDir);
    }

    void Forest::SetMaxHeightsRecurse(ForestCoordinates&& pos, int16_t height, Direction travelDir)
    {
        if ((pos.first <= 0) || (pos.first >= mDimensions.first)
            || (pos.second <= 0) || (pos.second >= mDimensions.second))
        {
            // end if we hit an edge
            return;
        }

        Tree& currTree = mGrid[pos.first][pos.second];
        {

            int16_t& maxHeight = currTree.mMaxHeights[static_cast<size_t>(travelDir)];
            
              if (height <= maxHeight)
              {
                  // early out if we already have this height
                  return;
              }
      

            maxHeight = height;
            
        }


        SetMaxHeightsRecurse(pos + kOffsets.at(static_cast<size_t>(travelDir)), height, travelDir);
    }

    //------------------------------------------------------------------------------
    bool Forest::CheckEdgeDirectionAllowed(const ForestCoordinates& pos, Direction dir) const
    {
        
        if (pos.first == 0)// Check Left Side
        {
            return dir == Direction::Right;
        }
        
        if (pos.first == mDimensions.first) // Check Right Side
        {
            return dir == Direction::Left;
        }
        
        if (pos.second == 0) // Top Side
        {
            return dir == Direction::Down;
        }
        
        if (pos.second == mDimensions.second) // Bottom Side
        {
            return dir == Direction::Up;
        }

        return true;
    }

    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        auto input = StringUtils::SplitFile(filename);

        Forest forest({input.size(), input[0].size()}, Forest::Mode::CalcHeightsOnAdd);

        for (const auto& line : input)
        {
            for (const char chHeight : line)
            {
                forest.AddNextTree(chHeight);
            }
        }

        const uint32_t numTrees = forest.CountVisibleTrees();

        std::cout << "The number of trees visible is: " << numTrees << std::endl;
        return numTrees;
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        auto input = StringUtils::SplitFile(filename);

        Forest forest({ input.size(), input[0].size() }, Forest::Mode::None);

        for (const auto& line : input)
        {
            for (const char chHeight : line)
            {
                forest.AddNextTree(chHeight);
            }
        }

        const uint32_t scenicScore = forest.GetScenicScore();

        std::cout << "The Max Scenic Score is: " << scenicScore << std::endl;
        return scenicScore;
    }
}