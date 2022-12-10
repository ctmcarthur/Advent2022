#pragma once

namespace DayTen
{
    class CRT
    {
    public:
        CRT();
        void PushNoop();
        void PushAdd(int32_t amt);
        int32_t GetValue(uint32_t cycleIdx) const;

    private:
        void FillToCycle(uint32_t newCycle);
        uint32_t mCurrentCycle = 1;
        std::vector<int32_t> mCycles;
    };
}