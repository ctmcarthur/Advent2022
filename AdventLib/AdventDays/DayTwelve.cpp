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


    class HeightMap
    {
    public:
        HeightMap(size_t width, size_t height);

        Node& GetNode(GridCoordinate location);
        uint32_t FindDistance(const Node& startNode, const Node& endNode);
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
        uint32_t FindDistance(const Node& startNode, const Node& goalNode);

    private:

        class SearchData
        {
        public:
            bool mSeen = false;
            uint32_t mDistance = 0;
        };

        void AddAdjacents(const Node& currNode, std::queue<const Node*>& nodeQueue);
        bool Visit(const Node& currNode);

        const Grid<Node>& mGrid;
        Grid<SearchData> mVisited;
        const Node* mGoal = nullptr;

    };

    BreadthFirstDistance::BreadthFirstDistance(const Grid<Node>& grid)
        : mGrid(grid)
        , mVisited(grid.GetWidth(), grid.GetHeight())
    {

    }

    uint32_t BreadthFirstDistance::FindDistance(const Node& startNode, const Node & goalNode)
    {
        mGoal = &goalNode;

        std::queue<const Node*> nodeQueue; 
        nodeQueue.push(&startNode);

        while (!nodeQueue.empty())
        {
            const Node& currNode = *nodeQueue.front();
            if (Visit(currNode))
            {
                // go to the end
                break;
            }

            AddAdjacents(currNode, nodeQueue);
            nodeQueue.pop();
        }

        return mVisited.at(goalNode.mLocation).mDistance;

    }

    bool BreadthFirstDistance::Visit(const Node& currNode)
    {
        SearchData& searchData = mVisited.at(currNode.mLocation);

        searchData.mSeen = true;

        return &currNode == mGoal;
    }

    void BreadthFirstDistance::AddAdjacents(const Node& currNode, std::queue<const Node*>& nodeQueue)
    {
        const auto nextDistance = mVisited.at(currNode.mLocation).mDistance + 1;

        // add adjacents
        for (const auto* const adjNode : currNode.mAdj)
        {
            SearchData& searchData = mVisited.at(adjNode->mLocation);

            if (searchData.mSeen)
            {
                continue;
            }

            searchData.mDistance = nextDistance;
            nodeQueue.push(adjNode);
        }
    }

    uint32_t HeightMap::FindDistance(const Node& startNode, const Node& endNode)
    {
        BreadthFirstDistance findAlg(mNodes);
        return findAlg.FindDistance(startNode, endNode);
    }

    bool TestIsAdjacent(const Node& start, const Node& end)
    {
        return (end.mHeight == 0) || (start.mHeight >= (end.mHeight - 1));
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

        heightMap.GenerateAdjacencies(&TestIsAdjacent);
        return heightMap;
    }

    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path & filename)
    {
       
        HeightMap heightMap = ParseHeightMap(filename);

        const uint32_t retVal = heightMap.FindDistance(heightMap.GetNode(heightMap.mStartIdx),
            heightMap.GetNode(heightMap.mEndIdx));

        std::cout << "The Answer is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint32_t>} };
    }

    //------------------------------------------------------------------------------
   // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        const uint32_t retVal = 0;

        std::cout << "The Answer is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint32_t>} };
    }
}