#pragma once

namespace DayEight
{
    enum class Direction : uint16_t
    {
        Left = 0,
        Right,
        Up,
        Down,
        COUNT
    };

    using ForestCoordinates = std::pair<size_t, size_t>;
   

    ForestCoordinates operator+(const ForestCoordinates& lhs, const ForestCoordinates& rhs);

    class Tree
    {
    public:
        int16_t height = -1;
        using DirectionArray = std::array<int16_t, static_cast<size_t>(Direction::COUNT)>;
        DirectionArray mMaxHeights = { -1, -1, -1, -1 };
    };

   

    class Forest
    {
    public:
        enum class Mode : uint16_t
        {
            None,
            CalcHeightsOnAdd
        };

        Forest(const ForestCoordinates& dimensions, Mode mode);
        // if adding trees one row a at time can use this.
        void AddNextTree(int16_t height);
        void AddTree(const ForestCoordinates& pos, int16_t height);
        uint32_t CountVisibleTrees() const;
        uint32_t GetScenicScore() const;

    private:

        // recursively tell our neighbors the max height tree from this direction
        void SetMaxHeights(const ForestCoordinates& pos, int16_t height, Direction travelDir);
        void SetMaxHeightsRecurse(ForestCoordinates&& pos, int16_t height, Direction travelDir);

        // if we are on the edge we only care about blocking in one direction towards the interior.
        bool CheckEdgeDirectionAllowed(const ForestCoordinates& pos, Direction dir) const;

        uint32_t CalcScenicScore(ForestCoordinates pos, int16_t height, Direction checkDir, uint32_t jumps) const;

        using ForestGrid = std::vector<std::vector<Tree>>;
        ForestCoordinates mDimensions = { 0,0 };
        Mode mMode = Mode::None;
        ForestGrid mGrid;
        ForestCoordinates mCurrentPos = { 0, 0 }; // for adding trees

    };
}