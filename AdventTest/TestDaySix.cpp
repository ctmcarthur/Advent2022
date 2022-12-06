#include "pch.h"

// Advent Lib
#include <AdventDays/DaySix.h>
// system

//------------------------------------------------------------------------------
// Test Helpers

namespace
{}

TEST(DaySix, TestPartOneExamples) 
{
    using namespace DaySix;
    constexpr uint32_t keySize = 4;
    EXPECT_EQ(FindFirstKeyIdx("mjqjpqmgbljsphdztnvjfqwrcgsmlb", keySize), 7ull);

    EXPECT_EQ(FindFirstKeyIdx("bvwbjplbgvbhsrlpgdmjqwftvncz", keySize), 5ull);

    EXPECT_EQ(FindFirstKeyIdx("nppdvjthqldpwncqszvftbrmjlhg", keySize), 6ull);

    EXPECT_EQ(FindFirstKeyIdx("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", keySize), 10ull);

    EXPECT_EQ(FindFirstKeyIdx("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", keySize), 11ull);
 //   EXPECT_EQ(blueprint.GetTopRow(), "NDP");
}
