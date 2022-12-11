#pragma once
// AdventLib
#include <Utilities/Hashing.h>

//------------------------------------------------------------------------------

class GridOffset
{
public:
    int32_t dX;
    int32_t dY;
};


class GridCoordinate
{
public:
    bool operator==(const GridCoordinate& rhs) const;
    GridOffset Distance(GridCoordinate& rhs) const;

    int32_t x = 0;
    int32_t y = 0;
};

template<typename T>
void BoostHash(size_t& seed, const T& value)
{
    std::hash<T> hasher;
    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std
{
    template<>
    struct hash<GridCoordinate>
    {
        size_t operator()(const GridCoordinate& value) const
        {
            unsigned long long result = 0ull; 
            BoostHash(result, value.x);
            BoostHash(result, value.y);
            return result;
        }
    };
}

GridCoordinate operator+(const GridCoordinate& lhs, const GridOffset& rhs);

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
    [[nodiscard]] size_t GetWidth() const { return mWidth; }
    [[nodiscard]] size_t GetHeight() const { return mWidth; }

    //------------------------------------------------------------------------------
    [[nodiscard]] T& at(GridCoordinate location)
    {
        assert(location.x < mWidth);
        assert(location.y < mHeight);

        return mGrid.at(location.y * mWidth + location.x);
    }

    [[nodiscard]] const T& at(GridCoordinate location) const
    {
        assert(location.x < mWidth);
        assert(location.y < mHeight);

        return mGrid.at(location.y * mWidth + location.x);
    }

    [[nodiscard]] T& operator[](GridCoordinate location)
    {
        return at(location);
    }

    [[nodiscard]] const T& operator[](GridCoordinate location) const
    {
        return at(location);
    }
   
    //------------------------------------------------------------------------------
    //  Iterators
    typename std::vector<T>::iterator begin() noexcept { return mGrid.begin(); }
    typename std::vector<T>::iterator end() noexcept { return mGrid.end(); }
    typename std::vector<T>::const_iterator begin() const noexcept { return mGrid.begin(); }
    typename std::vector<T>::const_iterator end() const noexcept { return mGrid.end(); }
    typename std::vector<T>::const_iterator cbegin() const noexcept { return mGrid.cbegin(); }
    typename std::vector<T>::const_iterator cend() const noexcept { return mGrid.cend(); }
    typename std::vector<T>::reverse_iterator rbegin() noexcept { return mGrid.rbegin(); }
    typename std::vector<T>::reverse_iterator rend() noexcept { return mGrid.rend(); }
    typename std::vector<T>::const_reverse_iterator rbegin() const noexcept { return mGrid.rbegin(); }
    typename std::vector<T>::const_reverse_iterator rend() const noexcept { return mGrid.rend(); }
    typename std::vector<T>::const_reverse_iterator crbegin() const noexcept { return mGrid.crbegin(); }
    typename std::vector<T>::const_reverse_iterator crend() const noexcept { return mGrid.crend(); }

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
std::ostream& operator<< (std::ostream& out, GridDirection dataSrc);
