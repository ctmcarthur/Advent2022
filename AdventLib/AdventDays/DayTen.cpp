#include "pch.h"
#include "DayTen.h"
// AdventLib
#include <Utilities/StringUtils.h>

/*
-noop   // 1 cycle
-addx  3 // after 2 cycles adds 3.


*/
namespace DayTen
{
    

    //------------------------------------------------------------------------------
    CRT::CRT()
    {

    }

    //------------------------------------------------------------------------------
    void CRT::PushNoop()
    {
        ++mCurrentCycle;
        FillToCycle(mCurrentCycle);
    }
    
    //------------------------------------------------------------------------------
    void CRT::PushAdd(int32_t amt)
    {
        static constexpr uint32_t kAddCycles = 2;
        mCurrentCycle += kAddCycles;
        FillToCycle(mCurrentCycle);
        mCycles.back() += amt;
    }

    //------------------------------------------------------------------------------
    void CRT::FillToCycle(uint32_t newCycle)
    {
        if (mCycles.empty())
        {
            mCycles.push_back(1);
        }

        const auto fillVal = mCycles.back();
        while (mCycles.size() <= newCycle)
        {
            mCycles.push_back(fillVal);
        }
    }

    //------------------------------------------------------------------------------
    int32_t CRT::GetValue(uint32_t cycleIdx) const
    {
        if (cycleIdx >= mCycles.size())
        {
            return mCycles.back();
        }

        return mCycles.at(cycleIdx);
    }

    
    //------------------------------------------------------------------------------
    // parsing
    void ParseInstruction(const std::string& line, CRT &crt)
    {
        static constexpr char kNoopChar = 'n';
        static constexpr char kAddChar = 'a';
        static constexpr size_t kAddValIdx = 5;

        if (line.at(0) == kNoopChar)
        {
            crt.PushNoop();
            return;
        }

        const int32_t addVal = std::stoi(line.substr(kAddValIdx));
        crt.PushAdd(addVal);
    }

    //------------------------------------------------------------------------------
    std::any DoPartOne(const std::string& filename)
    {
        CRT crt;

        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            ParseInstruction(line, crt);
        }

        //calc strength
        static constexpr std::array<uint32_t, 6> kSignals({20, 60, 100, 140, 180, 220});

        uint32_t signalSum = 0;
        for (auto signalIdx : kSignals)
        {
            signalSum += signalIdx * crt.GetValue(signalIdx);
        }
        std::cout << "The Signal Strength Sum is: " << signalSum << std::endl;

        return signalSum;
    }

    std::any DoPartTwo(const std::string& filename)
    {
        CRT crt;

        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            ParseInstruction(line, crt);
        }

        auto crtLines = crt.GetCycles() | std::ranges::views::chunk(40);

        for (auto crtLine : crtLines)
        {
            std::cout << std::endl;
            int32_t drawPos = 0;
            for (auto pixel : crtLine)
            {
                // are we within 1?
                if (std::abs(pixel - drawPos) <= 1)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }

                ++drawPos;
            }
            std::cout << std::endl;
        }
        return {};
    }
}