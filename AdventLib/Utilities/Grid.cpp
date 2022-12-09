#include "pch.h"
#include "Grid.h"

// AdventLib
#include <Utilities/EnumArray.h>

//------------------------------------------------------------------------------
// Grid Coordinate

bool GridCoordinate::operator==(const GridCoordinate& rhs) const
{
    return x == rhs.x && y == rhs.y;
}

GridOffset GridCoordinate::Distance(GridCoordinate& rhs) const
{
    return { static_cast<int32_t>(x - rhs.x), static_cast<int32_t>(y - rhs.y)};
}

GridCoordinate operator+(const GridCoordinate& lhs, const GridOffset& rhs)
{
    return { lhs.x + rhs.first, lhs.y + rhs.second };
}
/*
GridCoordinate operator+(const GridCoordinate& lhs, const GridCoordinate& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}*/

//------------------------------------------------------------------------------
// Direction

namespace
{
    using ShiftArray = EnumArray<GridDirection, GridOffset>;
    static constexpr ShiftArray kDirectionOffsets(ShiftArray::DataType(
        {
           {int32_t{-1}, int32_t{0}}, // Left
           {int32_t{1}, int32_t{0}}, // Right
           {int32_t{0}, int32_t{-1}}, // Up
           {int32_t{0}, int32_t{1}}  // Down
        }));
}


//------------------------------------------------------------------------------
GridCoordinate ShiftOnGrid(GridCoordinate pos, GridDirection dir)
{     
    const auto& offset = kDirectionOffsets[dir];

   // assert(offset.first >= 0 || pos.x > 0);
   // assert(offset.second >= 0 || pos.y > 0);
    return pos + offset;
}