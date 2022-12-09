#pragma once
// AdventLib
#include <Utilities/Grid.h>
namespace DayNine
{
    class RopeGrid
    {
    public:
        RopeGrid();

        void MoveHead(GridDirection direction);
        void MoveHead(GridDirection direction, int32_t repeat);

        size_t GetUniqueVisited() const { return mTailVisited.size(); }

    private:
        void PullTail();

        GridCoordinate mHeadPos = { 0,0 };
        GridCoordinate mTailPos = { 0,0 };

        std::unordered_set<uint32_t> mTailVisited;
        const int32_t mMaxDistance = 1;
    };
}