#pragma once
#include "pch.h"
#include "DayFive.h"

// AdventLib
#include <Utilities/StringUtils.h>

// System
#include <deque>

namespace DayFive
{
    //------------------------------------------------------------------------------

    class CraneInstruction
    {
    public:
        uint32_t count = 1;
        size_t source = 0;
        size_t dest = 1;
    };

    enum class CraneVersion : uint8_t 
    {
        CRANE_9000,
        CRANE_9001
    };

    class SupplyStacksBlueprint
    {
    public:
        void AddBottomCrate(size_t stackIdx, char boxLabel);
        void ExecuteCraneInstruction(const CraneInstruction& instructions, CraneVersion craneType);

        std::string GetTopRow() const;

    private:
        void MoveCrates(const CraneInstruction& instructions);
        void MoveCratesAsStack(const CraneInstruction& instructions);
    
        using BoxStack = std::deque<char>;
        std::pair<BoxStack&, BoxStack&> GetSrcDst(const CraneInstruction& instructions);
        std::vector<BoxStack> mStacks; // front is top of stack
    };
}