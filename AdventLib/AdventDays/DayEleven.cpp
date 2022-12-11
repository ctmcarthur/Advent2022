#include "pch.h"
#include "DayEleven.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/StringUtils.h>

namespace DayEleven2022
{
    //------------------------------------------------------------------------------
    // Constants
     // Monkey Parsing
    static constexpr size_t kNumLinesForMonkey = 7;
    // StartingItems:
    static constexpr size_t kStartingItemsLine = 1;
    static constexpr size_t kStartingItemIdx = 18;
    //Operation:
    static constexpr size_t kOperationLine = kStartingItemsLine + 1;
    static constexpr size_t kOperationTypeIdx = 23;
    static constexpr size_t kOperationValueIdx = 25;
    static constexpr char kOldSignifier = 'o';
    //Test
    static constexpr size_t kTestIdx = kOperationLine + 1;
    static constexpr size_t kTestValueIdx = 21;
    //True
    static constexpr size_t kTrueIdx = kTestIdx + 1;
    static constexpr size_t kTrueVal = 29;
    // False
    static constexpr size_t kFalseIdx = kTrueIdx + 1;
    static constexpr size_t kFalseVal = 30;

    class Monkey;

    using WorryVal = uint64_t;
    using MonkeyId = size_t;

    class MonkeyGang
    {
    public:
        Monkey& AddMonkey();
        void DoRounds(uint32_t count);
        uint64_t CalculateMonkeyBusiness();

    private:
        void ExecuteRound();
        void ProcessMonkey(Monkey& monkey);

        std::vector<Monkey> mMonkeys;

    };

    class Monkey
    {
    public:

        std::queue<WorryVal> mItems;

        using OperationFunc = std::function<WorryVal(WorryVal)>;
        OperationFunc mOperation;
        OperationFunc mReliefFunc;

        using TestFunc = std::function<bool(WorryVal)>;
        TestFunc mTest;

        MonkeyId mTrueDest = 0;
        MonkeyId mFalseDest = 0;

        uint64_t mInspectionCount = 0;
    }; 

    //------------------------------------------------------------------------------
    Monkey& MonkeyGang::AddMonkey()
    {
        mMonkeys.push_back({});
        return mMonkeys.back();
    }

    uint64_t MonkeyGang::CalculateMonkeyBusiness()
    {
        assert(mMonkeys.size() > 1);

        std::partial_sort(mMonkeys.begin(), mMonkeys.begin() + 2, mMonkeys.end(),
            [](const Monkey& rhs, const Monkey& lhs) -> bool {return rhs.mInspectionCount > lhs.mInspectionCount; });

        return mMonkeys[0].mInspectionCount * mMonkeys[1].mInspectionCount;
    }

    void MonkeyGang::DoRounds(uint32_t count)
    {
        for (uint32_t i = 0; i < count; ++i)
        {
            ExecuteRound();
        }
    }   

    void MonkeyGang::ExecuteRound()
    {
        for (auto& monkey : mMonkeys)
        {
            ProcessMonkey(monkey);
        }
    }

    void MonkeyGang::ProcessMonkey(Monkey& monkey)
    {
        while (!monkey.mItems.empty())
        {
            WorryVal& item = monkey.mItems.front();
            // operation
            item = monkey.mOperation(item);
            // relief
            item = monkey.mReliefFunc(item);
      
            //test
            const bool testResult = monkey.mTest(item);
            const MonkeyId monkeyIdx = testResult ? monkey.mTrueDest : monkey.mFalseDest;

            // toss
            mMonkeys.at(monkeyIdx).mItems.push(item);

            // record
            monkey.mInspectionCount++;
            monkey.mItems.pop();
        }
    }

    void ParseMonkey(const auto& monkeyInstructions, Monkey::OperationFunc reliefFunc, MonkeyGang& gang)
    {            
        Monkey& monkey = gang.AddMonkey();
       
        {
            // starting items.
            const std::string& startingItems = monkeyInstructions[kStartingItemsLine];
            const auto& items = StringUtils::SplitString<uint32_t>(startingItems.substr(kStartingItemIdx), ",");

            for (auto item : items)
            {
                monkey.mItems.push(item);
            }
        }
        {
            // operation
            const std::string& operationLine = monkeyInstructions[kOperationLine];
            const char operationType = operationLine[kOperationTypeIdx];

            if (operationType == '+')
            {
                const int32_t addValue = std::stoi(operationLine.substr(kOperationValueIdx));
                monkey.mOperation = [addValue](WorryVal worry) -> WorryVal { return worry + addValue; };
            }
            else
            {
                const char mulType = operationLine[kOperationValueIdx];
                
                if (mulType == kOldSignifier)
                {
                    monkey.mOperation = [](WorryVal worry) -> WorryVal { return worry * worry; };
                }
                else
                {
                    const int32_t mulValue = std::stoi(operationLine.substr(kOperationValueIdx));
                    monkey.mOperation = [mulValue](WorryVal worry) -> WorryVal { return worry * mulValue; };
                }
            }
        }       

        // Relief func
        monkey.mReliefFunc = reliefFunc;

        {
            // test
            const std::string& testLine = monkeyInstructions[kTestIdx];
            const uint64_t divisor = std::stoi(testLine.substr(kTestValueIdx));
           // monkey.mTest = TestDivisible(divisor);
            monkey.mTest = [divisor](WorryVal value) -> bool {return (value % divisor) == 0; };
        }

        {
            // true
            const std::string& trueLine = monkeyInstructions[kTrueIdx];
            const MonkeyId trueMonkey = std::stoi(trueLine.substr(kTrueVal));
            monkey.mTrueDest = trueMonkey;
        }

        {
            // false
            const std::string& falseLine = monkeyInstructions[kFalseIdx];
            const MonkeyId falseMonkey = std::stoi(falseLine.substr(kFalseVal));
            monkey.mFalseDest = falseMonkey;
        }                  
    }

    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);
        MonkeyGang gang;
        auto monkeyInputs = input | std::ranges::views::chunk(kNumLinesForMonkey);
       
        constexpr auto ReliefFunc = [](WorryVal worry) -> WorryVal { return worry / 3; };

        for (const auto& monkeyInstructions : monkeyInputs )
        {
            ParseMonkey(monkeyInstructions, ReliefFunc, gang);
        }       

        static constexpr uint32_t kNumRounds = 20;
        gang.DoRounds(kNumRounds);
        const auto retVal = gang.CalculateMonkeyBusiness();

        std::cout << "The Level Of Monkey Business is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint64_t>} };
    }

    //------------------------------------------------------------------------------
    // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        const auto input = StringUtils::SplitFile(filename);

        MonkeyGang gang;
        auto monkeyInputs = input | std::ranges::views::chunk(kNumLinesForMonkey);

        uint64_t maxDivisor = 1;

        for (const auto& monkeyInstructions : monkeyInputs)
        {
            const std::string& testLine = monkeyInstructions[kTestIdx];
            const uint64_t divisor = std::stoi(testLine.substr(kTestValueIdx));
            maxDivisor *= divisor;
        }
       
        auto reliefByModulus = [maxDivisor](WorryVal value) -> WorryVal { return (value % maxDivisor); };

        for (const auto& monkeyInstructions : monkeyInputs)
        {
            ParseMonkey(monkeyInstructions, reliefByModulus, gang);
        }

        static constexpr uint32_t kNumRounds = 10000;
        gang.DoRounds(kNumRounds);
        const auto retVal = gang.CalculateMonkeyBusiness();

        std::cout << "The Insanely High Level Of Monkey Business is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint64_t>} };
    }
}