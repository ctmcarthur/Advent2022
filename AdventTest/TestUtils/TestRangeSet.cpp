#include "pch.h"
#include <gtest/gtest.h>
#include <set>

#include <Utilities/Range.h>

TEST(TestRangeSet, TestNoOverlap)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 0,2 });
    ranges.InsertRange({ 5,6 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 2);
    EXPECT_EQ(rangeSet.count({ 0, 2 }), 1);
    EXPECT_EQ(rangeSet.count({ 5, 6 }), 1);
    EXPECT_EQ(CountUniqueValues(rangeSet), 5u);
}

TEST(TestRangeSet, TestOverlapMin)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 1,3 });
    ranges.InsertRange({ 5,10 });
    ranges.InsertRange({ 9,12 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 2);
    EXPECT_EQ(rangeSet.count({ 1, 3 }), 1);
    EXPECT_EQ(rangeSet.count({ 5, 12 }), 1);

    EXPECT_EQ(CountUniqueValues(rangeSet), 11u);
}

TEST(TestRangeSet, TestOverlapMax)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 1,5 });
    ranges.InsertRange({ 4,7 });
    ranges.InsertRange({ 9,12 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 2);
    EXPECT_EQ(rangeSet.count({ 1, 7 }), 1);
    EXPECT_EQ(rangeSet.count({ 9, 12 }), 1);

    EXPECT_EQ(CountUniqueValues(rangeSet), 11u);
}

TEST(TestRangeSet, TestOverlapBoth)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 2,5 });
    ranges.InsertRange({ 3,7 });
    ranges.InsertRange({ 5,6 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 1);
    EXPECT_EQ(rangeSet.count({ 2, 7 }), 1);

    EXPECT_EQ(CountUniqueValues(rangeSet), 6u);
}

TEST(TestRangeSet, TestOverlapComplete)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 2,5 });
    ranges.InsertRange({ 4,7 });
    ranges.InsertRange({ 9,12 });
    ranges.InsertRange({ 0,50 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 1);
    EXPECT_EQ(rangeSet.count({ 0, 50 }), 1);
    EXPECT_EQ(CountUniqueValues(rangeSet), 51u);
}

TEST(TestRangeSet, TestEmpty)
{
    RangeSet ranges;
    // Insert some ranges into the set
    ranges.InsertRange({ 1,1 });
    ranges.InsertRange({ 3,7 });
    ranges.InsertRange({ 1, 2 });

    const auto& rangeSet = ranges.GetRanges();
    // Verify that the set contains the expected ranges
    EXPECT_EQ(rangeSet.size(), 2);
    EXPECT_EQ(rangeSet.count({ 1, 2 }), 1);
    EXPECT_EQ(rangeSet.count({ 3, 7 }), 1);

    EXPECT_EQ(CountUniqueValues(rangeSet), 7u);
}