#pragma once

// System
#include <deque>

namespace DayFive
{
    //------------------------------------------------------------------------------
    using BoxStack = std::deque<char>; // front is top of stack.

    class CrateInstruction
    {
    public:
        uint32_t count = 1;
        size_t source = 0;
        size_t dest = 1;
    };

    class SupplyStacksBlueprint
    {
    public:
        void AddBottomCrate(size_t stackIdx, char boxLabel);
        void MoveCrates(const CrateInstruction& instructions);
        void MoveCratesAsStack(const CrateInstruction& instructions);

        const std::vector<BoxStack>& GetStacks() const { return mStacks; }

    private:
        std::vector<BoxStack> mStacks;
    };

    std::string GetTopRow(const SupplyStacksBlueprint& blueprint);
}