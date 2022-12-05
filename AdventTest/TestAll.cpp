#include "pch.h"

// Advent Lib
#include <AdventCalendar.h>

// system
#include <any>
#include <cassert>
#include <functional>
#include <optional>
#include <string>

//------------------------------------------------------------------------------
// Test Helpers
namespace
{
    //------------------------------------------------------------------------------
    // Answer Key

    template<typename T>
    bool CompareAny(const std::any& lhs, const std::any& rhs)
    {
        assert(lhs.type() == typeid(T));
        assert(rhs.type() == typeid(T));

        return std::any_cast<T>(lhs) == std::any_cast<T>(rhs);
    }

    class DayAnswerKey
    {
    public:
        using CompareFunc = std::function<bool(const std::any& lhs, const std::any& rhs)>;

        CompareFunc mCompareFunc;
        std::any mPartOneAnswer; 
        std::any mPartTwoAnswer; // might not solve part two.
    };

    // DataKey for each day's type of data. 
    using DataToDayAnswers = std::map<PuzzleInputType, DayAnswerKey>;
    // All days to all data 
    using CalenderAnswerKey = std::map<DayId, DataToDayAnswers>;

    const CalenderAnswerKey kAnswerKey =
    {
        {1,
            {
                {PuzzleInputType::ExampleData, {&CompareAny<uint32_t>, {24000u}, {45000u}}},
                {PuzzleInputType::RealData, {&CompareAny<uint32_t>, {68292u}, {203203u}}}
            }
        },
        {5,
            {
                {PuzzleInputType::ExampleData, {&CompareAny<std::string>, {std::string("CMZ")}, {std::string("MCD")}}},
                {PuzzleInputType::RealData, {&CompareAny<std::string>, {std::string("FCVRLMVQP")}, {std::string("RWLWGJGFD")}}}
            }
        }
    };

    //------------------------------------------------------------------------------
    // Using The Answer Key

    void TestDay(const AdventCalendar& calender, DayId day, PuzzleInputType dataType, const DayAnswerKey& answerKey)
    {
        // test Part One.
        {
            const auto partOneAnswer = calender.GetAnswer(day, PuzzleSection::PartOne, dataType);

            EXPECT_TRUE(answerKey.mCompareFunc(partOneAnswer, answerKey.mPartOneAnswer));
        }
        
        // part two is optional
        if (answerKey.mPartTwoAnswer.has_value())
        {
           const auto partTwoAnswer = calender.GetAnswer(day, PuzzleSection::PartTwo, dataType);
           EXPECT_TRUE(answerKey.mCompareFunc(partTwoAnswer, answerKey.mPartTwoAnswer));
        }    
    }

    void TestAllDays(const AdventCalendar& calender, PuzzleInputType dataType)
    {
        for (const auto& [day, dataToDayAnswers] : kAnswerKey)
        {
            const auto findIter = dataToDayAnswers.find(dataType);

            if (findIter != dataToDayAnswers.end())
            {
                TestDay(calender, day, dataType, findIter->second);
            }
        }
    }
    
}

TEST(TestAll, TestExampleData) 
{
    AdventCalendar calender;

    TestAllDays(calender, PuzzleInputType::ExampleData);
}

TEST(TestAll, TestRealData)
{
    AdventCalendar calender;

    TestAllDays(calender, PuzzleInputType::RealData);
}