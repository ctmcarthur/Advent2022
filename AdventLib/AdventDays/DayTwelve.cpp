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
    
    using AdjacenyFunc = std::function<void(Node&, const Node&)>;


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
        bool DepthFirstSearch(const Node& currentNode, const Node& endNode, Grid<uint32_t>& distances);
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
            adjacencyFunc(node, mNodes.at(*neighborCoord));
        }
    }

    class SearchData
    {
    public:
        bool mSeen = false;
        uint32_t mDistance = 0;
    };

    class BreadthFirstDistance
    {
    public:
        explicit BreadthFirstDistance(const Grid<Node>& grid);
        uint32_t FindDistance(const Node& startNode, const Node& goalNode);

    private:
        bool Search(const Node& currentNode);
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
        Search(startNode);

        std::queue<const Node*> nodeQueue; 
        nodeQueue.push(&startNode);

        while (nodeQueue.empty())
        {
            const Node& currNode = *nodeQueue.front();
            if (Visit(currNode))
            {
                break;
            }

            AddAdjacents(currNode, nodeQueue);
        }

        return mVisited.at(goalNode.mLocation).mDistance;

    }

    void BreadthFirstDistance::AddAdjacents(const Node& currNode, std::queue<const Node*> nodeQueue)
    {
        const auto nextDistance = mVisited.at(currNode.mLocation).mDistance;

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
    bool BreadthFirstDistance::Search(const Node& currentNode)
    {
        const auto& currentDistance = mVisited.at(currentNode.mLocation).mDistance;

        std::queue<Node> adjNodes;

        for 

    }

    uint32_t HeightMap::FindDistance(const Node& startNode, const Node& endNode)
    {
        // Depth First Search
        Grid<uint32_t> distances(mNodes.GetWidth(), mNodes.GetHeight());
        distances.at(startNode.mLocation) = 0;
        DepthFirstSearch(startNode, endNode, distances);

        return distances.at(mEndIdx);
    }

    bool HeightMap::DepthFirstSearch(const Node& currentNode, const Node& endNode, Grid<uint32_t>& distances)
    {  
        const auto& currentDistance = distances.at(currentNode.mLocation);

        for (const auto* const adjNode : currentNode.mAdj)
        {
            distances.at(adjNode->mLocation) = currentDistance + 1;
            if (adjNode == &endNode)
            {
                // found the end! 
                return true;
            }

            if (DepthFirstSearch(*adjNode, endNode, distances))
            {
                // stop calculating if end was found.
                return true;
            }
        }

        return false;
    }


    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path & filename)
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