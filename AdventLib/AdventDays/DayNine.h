#pragma once
// AdventLib
#include <Utilities/Grid.h>
namespace DayNine
{
    class RopeGrid
    {
    public:
        RopeGrid();
        explicit RopeGrid(size_t knotCount);

        void MoveHead(GridDirection direction);
        void MoveHead(GridDirection direction, int32_t repeat);

        size_t GetUniqueVisited() const { return mTailVisited.size(); }
        const GridCoordinate& GetHead() const { return mKnots.front(); }
        const GridCoordinate& GetTail() const { return mKnots.back(); }

    private:
        void RecordTail(const GridCoordinate& tailPos);

        std::vector<GridCoordinate> mKnots;
        std::unordered_set<GridCoordinate> mTailVisited;
    };
}