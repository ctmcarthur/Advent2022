#include "pch.h"
#include "DayEleven.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/StringUtils.h>

namespace DayEleven2022
{
    //------------------------------------------------------------------------------
    // Constants



    using WorryVal = int32_t;
    using MonkeyId = size_t;

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

    //------------------------------------------------------------------------------
    Monkey& MonkeyGang::AddMonkey()
    {
        mMonkeys.push_back({});
        return mMonkeys.back();
    }

    void MonkeyGang::DoRounds(uint32_t count)
    {
        for (uint32_t i = 0; i < count; ++i)
        {
            ExecuteRound();
        }
    }

    uint64_t MonkeyGang::CalculateMonkeyBusiness()
    {
        assert(mMonkeys.size() > 1);

        std::partial_sort(mMonkeys.begin(), mMonkeys.begin() + 2, mMonkeys.end(),
            [](const Monkey& rhs, const Monkey& lhs) -> bool {return rhs.mInspectionCount > lhs.mInspectionCount; });

        return mMonkeys[0].mInspectionCount * mMonkeys[1].mInspectionCount;
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

    //------------------------------------------------------------------------------
    // Operators
    class MultiplyWorry
    {
    public:
        MultiplyWorry() = default;
        explicit MultiplyWorry(int32_t value) : mValue(value) {}
        WorryVal operator()(WorryVal value) { return value * mValue; }

        int32_t mValue = 0;
    };

    class AddWorry
    {
    public:
        AddWorry() = default;
        explicit AddWorry(int32_t value) : mValue(value) {}
        WorryVal operator()(WorryVal value) { return value + mValue; }

        int32_t mValue = 0;
    };

    class TestDivisible
    {
    public:
        TestDivisible() = default;
        explicit TestDivisible(int32_t value) : mValue(value) { assert(mValue != 0); }
        bool operator()(WorryVal value)
        {
            return (value % mValue) == 0;;
        }

        int32_t mValue = 0;
    };

    constexpr auto SquareWorry = [](WorryVal worry) -> WorryVal { return worry * worry; };
    constexpr auto ReliefFunc = [](WorryVal worry) -> WorryVal { return worry / 3; };
    constexpr auto UnRelievedFunc = [](WorryVal worry) -> WorryVal { return worry; };



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
                monkey.mOperation = AddWorry(addValue);
            }
            else
            {
                const char mulType = operationLine[kOperationValueIdx];

                if (mulType == kOldSignifier)
                {
                    monkey.mOperation = SquareWorry;
                }
                else
                {
                    const int32_t mulValue = std::stoi(operationLine.substr(kOperationValueIdx));
                    monkey.mOperation = MultiplyWorry(mulValue);
                }
            }

        }

        // relief
        monkey.mReliefFunc = reliefFunc;

        {
            // test
            const std::string& testLine = monkeyInstructions[kTestIdx];
            const int32_t diviser = std::stoi(testLine.substr(kTestValueIdx));
            monkey.mTest = TestDivisible(diviser);
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

        for (const auto& monkeyInstructions : monkeyInputs)
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

        for (const auto& monkeyInstructions : monkeyInputs)
        {
            ParseMonkey(monkeyInstructions, UnRelievedFunc, gang);
        }

        static constexpr uint32_t kNumRounds = 10000;
        gang.DoRounds(kNumRounds);
        const auto retVal = gang.CalculateMonkeyBusiness();

        std::cout << "The Insanely High Level Of Monkey Business is: " << retVal << std::endl;

        return { {retVal}, {&CompareAny<uint64_t>} };
    }
}