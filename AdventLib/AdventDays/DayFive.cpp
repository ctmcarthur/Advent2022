#include "pch.h"
#include "DayFive.h"

// AdventLib
#include <Utilities/StringUtils.h>

namespace DayFive
{
    //------------------------------------------------------------------------------
    // SupplyStacksBlueprint

    void SupplyStacksBlueprint::AddBottomCrate(size_t stackIdx, char boxLabel)
    {
        assert(stackIdx < 10);
        if (mStacks.size() <= stackIdx)
        {
            mStacks.resize(stackIdx + 1);
        }

        mStacks.at(stackIdx).push_back(boxLabel);
    }

    void ValidateInstructions(const CrateInstruction& instructions, const std::vector<BoxStack> & stacks)
    {
        assert(instructions.source < stacks.size());
        assert(instructions.dest < stacks.size());
        assert(instructions.count > 0);
    }

    //------------------------------------------------------------------------------
    void SupplyStacksBlueprint::MoveCrates(const CrateInstruction& instructions)
    {
        ValidateInstructions(instructions, mStacks);

        BoxStack& src = mStacks[instructions.source];
        BoxStack& dst = mStacks[instructions.dest];
        
        assert(instructions.count <= src.size());

        for (uint32_t i = 0; i < instructions.count; ++i)
        {
            dst.push_front(src.front());
            src.pop_front();
        }
    }

    //------------------------------------------------------------------------------
    void SupplyStacksBlueprint::MoveCratesAsStack(const CrateInstruction& instructions)
    {
        ValidateInstructions(instructions, mStacks);

        BoxStack& src = mStacks[instructions.source];
        BoxStack& dst = mStacks[instructions.dest];

        assert(instructions.count <= src.size());

        std::stack<char> moveStack;

        for (uint32_t i = 0; i < instructions.count; ++i)
        {
            moveStack.push(src.front());
            src.pop_front();
        }

        while (!moveStack.empty())
        {
            dst.push_front(moveStack.top());
            moveStack.pop();
        }
    }

    //------------------------------------------------------------------------------
    std::string GetTopRow(const SupplyStacksBlueprint& blueprint)
    {
        std::string ret;
        const auto& stacks = blueprint.GetStacks();
        
        for (const auto& crateStack : stacks)
        {
            if (!crateStack.empty()) 
            {
                ret += crateStack.front();
            }
        }

        return ret;
    }

    //------------------------------------------------------------------------------
    // Parsing Input


    constexpr char kParseCrate = '[';
    constexpr char kParseMove = 'm';

    void ParseCrate(const std::string& input, SupplyStacksBlueprint& inOutBlueprint)
    {
        for (size_t i = 0; i < input.size(); ++i)
        {
            if (input.at(i) == kParseCrate)
            {
                assert(i + 1 < input.size());

                constexpr uint32_t idxFactor = 4;
                inOutBlueprint.AddBottomCrate(static_cast<uint32_t>(i/idxFactor), input.at(i + 1));
                ++i;
            }
        }
    }

    //------------------------------------------------------------------------------
    void ParseMove(const std::string& input, CrateInstruction &outInstructions)
    {
        constexpr size_t countIdx = 5;
        const size_t srcIdx = input.find('m', countIdx) + 2;
        const size_t dstIdx = input.find_last_of(' ') + 1;

        outInstructions.count = static_cast<uint32_t>(std::stoi(input.substr(countIdx)));
        outInstructions.source = static_cast<size_t>(std::stoi(std::string{ input.at(srcIdx) })) - 1;
        outInstructions.dest = static_cast<size_t>(std::stoi(std::string{ input.at(dstIdx) })) - 1;
    }

    //------------------------------------------------------------------------------
    // Part One
   

    //------------------------------------------------------------------------------
    // Do Part One
    std::any DoPartOne(const std::string& filename)
    {
        const auto input = Utilities::ReadAllLinesInFile(filename);
        
        SupplyStacksBlueprint blueprint;
        
        for (const auto& line : input)
        {
            for (const char command : line)
            {
                if (command == kParseCrate)
                {
                    ParseCrate(line, blueprint);
                    break;
                }
                if (command == kParseMove)
                {
                    CrateInstruction instructions;
                    ParseMove(line, instructions);
                    blueprint.MoveCrates(instructions);
                    break;
                }
            }
        }

        std::string topRow = GetTopRow(blueprint);

        std::cout << "Top Row of Crates are labeled: " << topRow << std::endl;


        return topRow;
    }


    //------------------------------------------------------------------------------
    // Part 2

    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    std::any DoPartTwo(const std::string& filename)
    {
        const auto input = Utilities::ReadAllLinesInFile(filename);

        SupplyStacksBlueprint blueprint;

        for (const auto& line : input)
        {
            for (const char command : line)
            {
                if (command == kParseCrate)
                {
                    ParseCrate(line, blueprint);
                    break;
                }
                if (command == kParseMove)
                {
                    CrateInstruction instructions;
                    ParseMove(line, instructions);
                    blueprint.MoveCratesAsStack(instructions);
                    break;
                }
            }
        }

        std::string topRow = GetTopRow(blueprint);

        std::cout << "The Crane 9001 Stacked Crates are labeled: " << topRow << std::endl;


        return topRow;
    }
}