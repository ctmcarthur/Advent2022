#include "pch.h"
#include "DayTwelve.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/Grid.h>
#include <Utilities/StringUtils.h>

namespace DayTwelve2022
{

    
    class Node
    {
    public:
        uint32_t mHeight = 0;
        std::vector<Node*> mAdj;
        GridCoordinate mLocation;
    }; 
    
    using AdjacenyFunc = std::function<bool(const Node& start, const Node& end)>;
    using GoalFunc = std::function<bool(const Node& testNode)>;

    class HeightMap
    {
    public:
        HeightMap(size_t width, size_t height);

        Node& GetNode(GridCoordinate location);
        uint32_t FindDistance(const Node& startNode, GoalFunc goalFunc);
        void GenerateAdjacencies(AdjacenyFunc adjacencyFunc);
       
        Grid<Node> mNodes;
        GridCoordinate mStartIdx;
        GridCoordinate mEndIdx;

    private:
        void GenerateDirectionAdjacency(Node& node, AdjacenyFunc adjacencyFunc, GridDirection direction);
    };


    HeightMap::HeightMap(size_t width, size_t height)
        : mNodes(width, height)
    {

    }

    Node& HeightMap::GetNode(GridCoordinate location)
    {
        Node& newNode = mNodes.at(location);
        newNode.mLocation = location;
        return newNode;
    }

    void HeightMap::GenerateAdjacencies(AdjacenyFunc adjacencyFunc)
    { 
        for (auto& node : mNodes)
        {
            GenerateDirectionAdjacency(node, adjacencyFunc, GridDirection::Left);
            GenerateDirectionAdjacency(node, adjacencyFunc, GridDirection::Right);
            GenerateDirectionAdjacency(node, adjacencyFunc, GridDirection::Up);
            GenerateDirectionAdjacency(node, adjacencyFunc, GridDirection::Down);
        }
    }
    void HeightMap::GenerateDirectionAdjacency(Node& node, AdjacenyFunc adjacencyFunc, GridDirection direction)
    {
        if (auto neighborCoord = TryShiftOnGrid(node.mLocation, direction, mNodes.GetWidth(), mNodes.GetHeight()))
        {
            auto& nextNode = mNodes.at(*neighborCoord);
            if (adjacencyFunc(node, nextNode))
            {
                node.mAdj.push_back(&nextNode);
            }
        }
    }

    
    class BreadthFirstDistance
    {
    public:
        explicit BreadthFirstDistance(const Grid<Node>& grid);
        uint32_t FindDistance(const Node& startNode, GoalFunc goalFunc);

    private:

        class SearchData
        {
        public:
            bool mSeen = false;
            bool mAdded = false;
            uint32_t mDistance = 0;
        };

        void AddAdjacents(const Node& currNode, std::queue<const Node*>& nodeQueue);
        bool Visit(const Node& currNode);

        const Grid<Node>& mGrid;
        Grid<SearchData> mVisited;
        GoalFunc mGoalFunc;

    };

    BreadthFirstDistance::BreadthFirstDistance(const Grid<Node>& grid)
        : mGrid(grid)
        , mVisited(grid.GetWidth(), grid.GetHeight())
    {

    }

    uint32_t BreadthFirstDistance::FindDistance(const Node& startNode, GoalFunc goalFunc)
    {
        mGoalFunc = goalFunc;

        std::queue<const Node*> nodeQueue; 
        nodeQueue.push(&startNode);

        const Node* goalNode = nullptr;

        while (!nodeQueue.empty())
        {
            const Node& currNode = *nodeQueue.front();
            if (Visit(currNode))
            {
                goalNode = &currNode;
                // go to the end
                break;
            }

            AddAdjacents(currNode, nodeQueue);
            nodeQueue.pop();
        }

        assert(goalNode != nullptr);

        return mVisited.at(goalNode->mLocation).mDistance;

    }

    bool BreadthFirstDistance::Visit(const Node& currNode)
    {
        SearchData& searchData = mVisited.at(currNode.mLocation);

        searchData.mSeen = true;

        return mGoalFunc(currNode);
    }

    void BreadthFirstDistance::AddAdjacents(const Node& currNode, std::queue<const Node*>& nodeQueue)
    {
        const auto nextDistance = mVisited.at(currNode.mLocation).mDistance + 1;

        // add adjacents
        for (const auto* const adjNode : currNode.mAdj)
        {
            SearchData& searchData = mVisited.at(adjNode->mLocation);

            if (searchData.mSeen || searchData.mAdded)
            {
                continue;
            }

            searchData.mAdded = true;
            searchData.mDistance = nextDistance;
            nodeQueue.push(adjNode);
        }
    }

    uint32_t HeightMap::FindDistance(const Node& startNode, GoalFunc goalFunc)
    {
        BreadthFirstDistance findAlg(mNodes);
        return findAlg.FindDistance(startNode, goalFunc);
    }

    bool TestIsAdjacent(const Node& start, const Node& end)
    {
        return (end.mHeight == 0) || (start.mHeight >= (end.mHeight - 1));
    }

    bool TestGoingDownhill(const Node& start, const Node& end)
    {
        return start.mHeight <= (end.mHeight + 1);
    }

    //------------------------------------------------------------------------------
    // parsing
    HeightMap ParseHeightMap(const std::filesystem::path& filename)
    {
        static constexpr char kStartChar = 'S';
        static constexpr char kEndChar = 'E';

        const auto input = StringUtils::SplitFile(filename);
        assert(!input.empty());
        
        const size_t maxWidth = input.at(0).size();
        const size_t mapHeight = input.size();

        HeightMap heightMap(maxWidth, mapHeight);
        
        for (size_t x = 0; x < maxWidth; ++x)
        {   
            for (size_t y = 0; y < mapHeight; ++y)
            {
                const GridCoordinate coord{ static_cast<int32_t>(x), static_cast<int32_t>(y) };
                auto& node = heightMap.GetNode(coord);
                char height = input[y][x];

                if (height == kStartChar)
                {
                    height = 'a';
                    heightMap.mStartIdx = coord;
                }
                else if (height == kEndChar)
                {
                    height = 'z';
                    heightMap.mEndIdx = coord;
                }

                node.mLocation = coord;
                node.mHeight = height - 'a';
            }
        }

        return heightMap;
    }

    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path & filename)
    {
       
        HeightMap heightMap = ParseHeightMap(filename);
        heightMap.GenerateAdjacencies(&TestIsAdjacent);

        const Node* const goalNode = &heightMap.GetNode(heightMap.mEndIdx);
        auto findGoal = [goalNode](const Node& testNode) -> bool
            {return &testNode == goalNode; };

        const uint32_t pathLength = heightMap.FindDistance(heightMap.GetNode(heightMap.mStartIdx), findGoal);

        std::cout << "Fastest Path to top of the mountain is:  " << pathLength << " Steps." << std::endl;

        return { {pathLength}, {&CompareAny<uint32_t>} };
    }

    //------------------------------------------------------------------------------
   // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        HeightMap heightMap = ParseHeightMap(filename);
        heightMap.GenerateAdjacencies(&TestGoingDownhill);

        constexpr auto findGoal = [](const Node& testNode) -> bool
        {return testNode.mHeight == 0; };

        const uint32_t pathLength = heightMap.FindDistance(heightMap.GetNode(heightMap.mEndIdx), findGoal);

        std::cout << "Fastest Path to bottom of the mountain is:  " << pathLength << " Steps." << std::endl;

        return { {pathLength}, {&CompareAny<uint32_t>} };
    }
}