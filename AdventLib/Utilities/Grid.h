#pragma once
// AdventLib
#include <Utilities/Hashing.h>

//------------------------------------------------------------------------------

using GridOffset = std::pair<int32_t, int32_t>;

class GridCoordinate
{
public:
    bool operator==(const GridCoordinate& rhs) const;
    GridOffset Distance(GridCoordinate& rhs) const;

    int32_t x = 0;
    int32_t y = 0;
};

IMPLEMENT_STD_HASH(GridCoordinate, value.x, value.y);

GridCoordinate operator+(const GridCoordinate& lhs, const GridOffset& rhs);

//GridCoordinate operator+(const GridCoordinate& lhs, const GridCoordinate& rhs);

//------------------------------------------------------------------------------
template<class T>
class Grid
{
public:
    //------------------------------------------------------------------------------
    Grid(size_t width, size_t height)
        : mWidth(width)
        , mHeight(height)
        , mGrid(width*height)
    {

    }

    //------------------------------------------------------------------------------
    Grid(size_t width, size_t height, const T& defaultValue)
        : mWidth(width)
        , mHeight(height)
        , mGrid(width*height)
    {

    }

    //------------------------------------------------------------------------------
    size_t GetWidth() const { return mWidth; }
    size_t GetHeight() const { return mWidth; }

    //------------------------------------------------------------------------------
    T& at(GridCoordinate location)
    {
        assert(location.x < mWidth);
        assert(location.y < mHeight);

        return mGrid.at(location.y * mWidth + location.x);
    }

    const T& at(GridCoordinate location) const
    {
        assert(location.x < mWidth);
        assert(location.y < mHeight);

        return mGrid.at(location.y * mWidth + location.x);
    }

    T& operator[](GridCoordinate location)
    {
        return at(location);
    }

    const T& operator[](GridCoordinate location) const
    {
        return at(location);
    }
   
    //------------------------------------------------------------------------------
    //  Iterators
    std::vector<T>::iterator begin() noexcept { return mGrid.begin(); }
    std::vector<T>::iterator end() noexcept { return mGrid.end(); }
    std::vector<T>::const_iterator begin() const noexcept { return mGrid.begin(); }
    std::vector<T>::const_iterator end() const noexcept { return mGrid.end(); }
    std::vector<T>::const_iterator cbegin() const noexcept { return mGrid.cbegin(); }
    std::vector<T>::const_iterator cend() const noexcept { return mGrid.cend(); }
    std::vector<T>::reverse_iterator rbegin() noexcept { return mGrid.rbegin(); }
    std::vector<T>::reverse_iterator rend() noexcept { return mGrid.rend(); }
    std::vector<T>::const_reverse_iterator rbegin() const noexcept { return mGrid.rbegin(); }
    std::vector<T>::const_reverse_iterator rend() const noexcept { return mGrid.rend(); }
    std::vector<T>::const_reverse_iterator crbegin() const noexcept { return mGrid.crbegin(); }
    std::vector<T>::const_reverse_iterator crend() const noexcept { return mGrid.crend(); }

private:
    size_t mWidth;
    size_t mHeight;
    std::vector<T> mGrid;
};


//------------------------------------------------------------------------------
// Direction Math
enum class GridDirection : uint16_t
{
    Left = 0,
    Right,
    Up,
    Down,
    Last = Down
};

GridCoordinate ShiftOnGrid(GridCoordinate pos, GridDirection dir);
