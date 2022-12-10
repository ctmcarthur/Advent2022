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
        const std::vector<int32_t>& GetCycles() const { return mCycles; }

    private:
        void FillToCycle(uint32_t newCycle);
        uint32_t mCurrentCycle = 0;
        std::vector<int32_t> mCycles;
    };
}