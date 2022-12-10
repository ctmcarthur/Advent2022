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
                {PuzzleInputType::ExampleData, {{24000u}, {45000u}}},
                {PuzzleInputType::RealData, {{68292u}, {203203u}}}
            }
        },
        {2,
            {
                {PuzzleInputType::ExampleData, {{15u}, {12u}}},
                {PuzzleInputType::RealData, {{13268u}, {15508u}}}
            }
        },
        {3,
            {
                {PuzzleInputType::ExampleData, {{157u}, {70u}}},
                {PuzzleInputType::RealData, {{7997u}, {2545u}}}
            }
        },
        {4,
            {
                {PuzzleInputType::ExampleData, {{2u}, {4u}}},
                {PuzzleInputType::RealData, {{528u}, {881u}}}
            }
        },
        {5,
            {
                {PuzzleInputType::ExampleData, {{std::string("CMZ")}, {std::string("MCD")}}},
                {PuzzleInputType::RealData, {{std::string("FCVRLMVQP")}, {std::string("RWLWGJGFD")}}}
            }
        },
        {6,
            {
                {PuzzleInputType::ExampleData, {size_t{7}, size_t{19}}},
                {PuzzleInputType::RealData, {size_t{1034}, size_t{2472}}}
            }
        },
        {7,
            {
                {PuzzleInputType::ExampleData, {size_t{95437}, size_t{24933642}}},
                {PuzzleInputType::RealData, {size_t{1428881}, size_t{10475598}}}
            }
        },
        {8,
            {
                {PuzzleInputType::ExampleData, {{21u}, {8u}}},
                {PuzzleInputType::RealData, {{1533u}, {345744u}}}
            }
        },
    };

    //------------------------------------------------------------------------------
    // Using The Answer Key

    void TestDay(const AdventCalendar& calender, DayId day, PuzzleInputType dataType, const DayAnswerKey& answerKey)
    {
        // test Part One.
        {
            std::cout << std::endl << "Testing day " << day << " Part One!" << std::endl << "----------------------" << std::endl;
            const auto partOneAnswer = calender.GetAnswer(day, PuzzleSection::PartOne, dataType);

            EXPECT_TRUE(partOneAnswer.mCompareFunc(partOneAnswer.mSolution, answerKey.mPartOneAnswer));
        }
        
        // part two is optional
        if (answerKey.mPartTwoAnswer.has_value())
        {
            std::cout << "Testing day " << day << " Part Two!" << std::endl << "----------------------" << std::endl;
           const auto partTwoAnswer = calender.GetAnswer(day, PuzzleSection::PartTwo, dataType);
           EXPECT_TRUE(partTwoAnswer.mCompareFunc(partTwoAnswer.mSolution, answerKey.mPartTwoAnswer));
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