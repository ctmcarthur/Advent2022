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

GridOffset GridCoordinate::Distance(const GridCoordinate& rhs) const
{
    return { static_cast<int32_t>(x - rhs.x), static_cast<int32_t>(y - rhs.y)};
}

constexpr GridCoordinate operator+(const GridCoordinate& lhs, const GridOffset& rhs)
{
    return { lhs.x + rhs.dX, lhs.y + rhs.dY };
}

//------------------------------------------------------------------------------
GridOffset NormalizeOffset(const GridOffset& offset)
{
    GridOffset normalized = { 0,0 };

    if (offset.dX != 0)
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

    if (offset.dY != 0)
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
// Direction

namespace
{
    using ShiftArray = EnumArray<GridDirection, GridOffset>;
    constexpr ShiftArray kDirectionOffsets(ShiftArray::DataType
        { {
           {int32_t{-1}, int32_t{0}}, // Left
           {int32_t{1}, int32_t{0}}, // Right
           {int32_t{0}, int32_t{-1}}, // Up
           {int32_t{0}, int32_t{1}}  // Down
        } });
}


//------------------------------------------------------------------------------
std::optional<GridCoordinate> TryShiftOnGrid(GridCoordinate pos, GridDirection dir, size_t width, size_t height)
{
    const GridCoordinate ret = ShiftOnGrid(pos, dir);

    if ((ret.x < 0) ||
        (ret.y < 0) ||
        (ret.x >= width) ||
        (ret.y >= height))
    {
        return {};
    }

    return ret;
}

//------------------------------------------------------------------------------
GridCoordinate ShiftOnGrid(GridCoordinate pos, GridDirection dir)
{     
    const auto& offset = kDirectionOffsets[dir];

   // assert(offset.first >= 0 || pos.x > 0);
   // assert(offset.second >= 0 || pos.y > 0);
    return pos + offset;
}

//------------------------------------------------------------------------------
std::ostream& operator<< (std::ostream& out, GridDirection dataSrc)
{
    switch (dataSrc)
    {
    case GridDirection::Left:
        out << "Left";
        break;

    case GridDirection::Right:
        out << "Right";
        break;
    
    case GridDirection::Up:
        out << "Up";
        break;

    case GridDirection::Down:
        out << "Down";
        break;
    }

    return out;
}

