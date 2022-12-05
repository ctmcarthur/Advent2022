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
        if (mStacks.size() <= stackIdx)
        {
            mStacks.resize(stackIdx + 1);
        }

        mStacks.at(stackIdx).push_back(boxLabel);
    }

    
    //------------------------------------------------------------------------------
    void SupplyStacksBlueprint::ExecuteCraneInstruction(const CraneInstruction& instructions, CraneVersion craneType)
    {
        switch (craneType)
        {
        case CraneVersion::CRANE_9000:
            MoveCrates(instructions);
            break;
        case CraneVersion::CRANE_9001:
            MoveCratesAsStack(instructions);
            break;
        }
    }

    //------------------------------------------------------------------------------
    std::pair<SupplyStacksBlueprint::BoxStack&, SupplyStacksBlueprint::BoxStack&> SupplyStacksBlueprint::GetSrcDst(
        const CraneInstruction& instructions)
    {
        assert(instructions.source < mStacks.size());
        assert(instructions.dest < mStacks.size());

        BoxStack& src = mStacks.at(instructions.source);
        BoxStack& dst = mStacks.at(instructions.dest);

        assert(instructions.count <= src.size());
        assert(instructions.count != 0);

        return { src, dst };
    }

    //------------------------------------------------------------------------------
    void SupplyStacksBlueprint::MoveCrates(const CraneInstruction& instructions)
    {
        
        auto [src, dst] = GetSrcDst(instructions);
        for (uint32_t i = 0; i < instructions.count; ++i)
        {
            dst.push_front(src.front());
            src.pop_front();
        }
    }

    //------------------------------------------------------------------------------
    void SupplyStacksBlueprint::MoveCratesAsStack(const CraneInstruction& instructions)
    {
        auto [src, dst] = GetSrcDst(instructions);

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
    std::string SupplyStacksBlueprint::GetTopRow() const
    {
        std::string ret;
        
        for (const auto& crateStack : mStacks)
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
    void ParseMove(const std::string& input, CraneInstruction &outInstructions)
    {
        constexpr size_t countIdx = 5;
        const size_t srcIdx = input.find('m', countIdx) + 2;
        const size_t dstIdx = input.find_last_of(' ') + 1;

        outInstructions.count = static_cast<uint32_t>(std::stoi(input.substr(countIdx)));
        outInstructions.source = static_cast<size_t>(std::stoi(std::string{ input.at(srcIdx) })) - 1;
        outInstructions.dest = static_cast<size_t>(std::stoi(std::string{ input.at(dstIdx) })) - 1;
    }

    std::string ParseAndExecute(const std::string& filename, CraneVersion craneVersion)
    {
        const auto input = StringUtils::SplitFile(filename);

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
                    CraneInstruction instructions;
                    ParseMove(line, instructions);
                    blueprint.ExecuteCraneInstruction(instructions, craneVersion);
                    break;
                }
            }
        }

        return blueprint.GetTopRow();
    }

    //------------------------------------------------------------------------------
    // Part One
   

    //------------------------------------------------------------------------------
    // Do Part One
    std::any DoPartOne(const std::string& filename)
    {
        std::string topRow = ParseAndExecute(filename, CraneVersion::CRANE_9000);

        std::cout << "Top Row of Crates are labeled: " << topRow << std::endl;


        return topRow;
    }


    //------------------------------------------------------------------------------
    // Part 2

    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    std::any DoPartTwo(const std::string& filename)
    {

        std::string topRow = ParseAndExecute(filename, CraneVersion::CRANE_9001);


        std::cout << "The Crane 9001 Stacked Crates are labeled: " << topRow << std::endl;


        return topRow;
    }
}