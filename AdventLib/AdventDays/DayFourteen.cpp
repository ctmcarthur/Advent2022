#include "pch.h"
#include "DayFourteen.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/Grid.h>
#include <Utilities/StringUtils.h>


namespace DayFourteen2022
{

    static constexpr size_t kGridWidth = 1000;
    static constexpr size_t kGridHeight = 400;
    static constexpr GridOffset kRockXOffset = { 0, 0 };
    static constexpr GridCoordinate kSandSource = { 500, 0 };

    enum class CellContents : uint32_t
    {
        Empty,
        Rock,
        Sand
    };

    enum class SimulateResult : uint32_t
    {
        Stopped,
        Abyss,
        Clogged
    };
    
    class Cavern
    {
    public:
        Cavern();
        void AddRock(const std::vector<GridCoordinate>& rock);
        void Print() const;
        SimulateResult SimulateSand();
        int32_t GetLowestPoint() const { return mLowestPoint; }

    private:
        void FillAllPieces(const GridCoordinate& start, const GridCoordinate& end);
        bool TryFill(const GridCoordinate& pos);

        Grid<CellContents> mGrid;
        int32_t mLowestPoint = 0;
    };

    void Cavern::Print() const
    {
        for (size_t y = 0; y < mGrid.GetHeight(); ++y)
        {
            std::string line;

            for (size_t x = 0; x < mGrid.GetWidth(); ++x)
            {
                switch (mGrid.at({ static_cast<int32_t>(x),static_cast<int32_t>(y)}))
                {
                case CellContents::Empty:
                    line += ".";
                    break;

                case CellContents::Rock:
                    line += "#";
                    break;
                    
                case CellContents::Sand:
                    line += "o";
                    break;
                }
            }

            std::cout << line << "\n";
        }
    }

    void Cavern::AddRock(const std::vector<GridCoordinate>& rock)
    {
        if (rock.empty())
        {
            return;
        }

        GridCoordinate lastRockPiece = rock.at(0) + kRockXOffset;

        mGrid.at(lastRockPiece) = CellContents::Rock;
        mLowestPoint = std::max(mLowestPoint, lastRockPiece.y);
        

        for (auto iter = std::next(rock.begin()); iter != rock.end(); ++iter)
        {
            GridCoordinate nextRockPiece = (*iter) + kRockXOffset;
            FillAllPieces(lastRockPiece, nextRockPiece);
            mLowestPoint = std::max(mLowestPoint, lastRockPiece.y);
            lastRockPiece = nextRockPiece;
        }
    }

    void Cavern::FillAllPieces(const GridCoordinate& start, const GridCoordinate& end)
    {
        assert((start.x == end.x)|| (start.y == end.y));
        const GridOffset distance = end.Distance(start);
        const GridOffset moveDirection = NormalizeOffset(distance);

        GridCoordinate current = start;
        while (current != end)
        {
            current = current + moveDirection;
            mGrid.at(current) = CellContents::Rock;
        }

    }

    //------------------------------------------------------------------------------
    Cavern::Cavern()
        : mGrid(kGridWidth, kGridHeight, CellContents::Empty)
    {

    }
    
    SimulateResult Cavern::SimulateSand()
    {
        GridCoordinate sandPos = kSandSource;
        
        while (sandPos.y <= mLowestPoint)
        {
            const GridCoordinate prevCoord = sandPos;
            // try to go straight down.
            const GridCoordinate down = ShiftOnGrid(sandPos, GridDirection::Down);
            sandPos = down;
            if (mGrid.at(sandPos) != CellContents::Empty)
            {
                // try left/down
                sandPos = ShiftOnGrid(down, GridDirection::Left);

                if (mGrid.at(sandPos) != CellContents::Empty)
                {
                    // try right/down
                    sandPos = ShiftOnGrid(down, GridDirection::Right);

                    if (mGrid.at(sandPos) != CellContents::Empty)
                    {
                        mGrid.at(prevCoord) = CellContents::Sand;

                        if (prevCoord == kSandSource)
                        {
                            return SimulateResult::Clogged;
                        }

                        return SimulateResult::Stopped;
                    }
                }
            }
        }

        return SimulateResult::Abyss;
    }
    void ParseCavern(const std::filesystem::path& filename, Cavern& cavern)
    {
        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            const auto& points = StringUtils::SplitString<std::string>(line, " -> ");
            std::vector<GridCoordinate> rockPoints;
            for (const auto& point : points)
            {
                const auto& values = StringUtils::SplitString<int32_t>(point, ",");
                assert(values.size() == 2);

                rockPoints.emplace_back(GridCoordinate{ values[0], values[1] });
            }

            assert(!rockPoints.empty());
            cavern.AddRock(rockPoints);
        }

    }
    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        Cavern cavern;
        ParseCavern(filename, cavern);

        uint32_t sandCount = 0;
        while (cavern.SimulateSand() == SimulateResult::Stopped)
        {
           ++sandCount;
        }
       
        std::cout << "The Number of Grains of sands until abyss is " << sandCount << "\n";

        return { {sandCount}, {&CompareAny<uint32_t>} };

    }

    //------------------------------------------------------------------------------
    // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        Cavern cavern;
        ParseCavern(filename, cavern);

        const auto lowestPoint = cavern.GetLowestPoint();

        std::vector<GridCoordinate> rockFloor;
        const GridCoordinate leftFloor{ 0 - kRockXOffset.dX, lowestPoint+2 };
        const GridCoordinate rightFloor{(kGridWidth-2) - kRockXOffset.dX, lowestPoint + 2 };

        rockFloor.push_back(leftFloor);
        rockFloor.push_back(rightFloor);
        cavern.AddRock(rockFloor);


       // cavern.Print();
        uint32_t sandCount = 1;
        while ((cavern.SimulateSand() == SimulateResult::Stopped))
        {
            ++sandCount;
        }


        std::cout << "The Number of Grains of sands until clogged is " << sandCount << "\n";

        return { {sandCount}, {&CompareAny<uint32_t>} };

    }
}