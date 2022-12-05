#include "pch.h"

// Advent Lib
#include <AdventDays/DayFive.h>
// system

//------------------------------------------------------------------------------
// Test Helpers

namespace
{
    void FillExampleData(DayFive::SupplyStacksBlueprint& blueprint)
    {
        using namespace DayFive;

        blueprint.AddBottomCrate(1, 'D');
        blueprint.AddBottomCrate(1, 'C');
        blueprint.AddBottomCrate(1, 'M');
        blueprint.AddBottomCrate(0, 'N');
        blueprint.AddBottomCrate(0, 'Z');
        blueprint.AddBottomCrate(2, 'P');
    }
}

TEST(DayFive, TestBoxLoading) 
{
    using namespace DayFive;
    SupplyStacksBlueprint blueprint;
    FillExampleData(blueprint);
    EXPECT_EQ(GetTopRow(blueprint), "NDP");
}

TEST(DayFive, PartOneBoxMoving)
{
    using namespace DayFive;
    SupplyStacksBlueprint blueprint;
    FillExampleData(blueprint);

    {
        blueprint.MoveCrates({ 1,1,0 });
        EXPECT_EQ(GetTopRow(blueprint), "DCP");
    }

    {
        blueprint.MoveCrates({ 3,0,2 });
        EXPECT_EQ(GetTopRow(blueprint), "CZ");
    }

    {
        blueprint.MoveCrates({ 2,1,0 });
        EXPECT_EQ(GetTopRow(blueprint), "MZ");
    }

    {
        blueprint.MoveCrates({ 1,0,1 });
        EXPECT_EQ(GetTopRow(blueprint), "CMZ");
    }
}

TEST(DayFive, PartTwoBoxMoving)
{
    using namespace DayFive;
    SupplyStacksBlueprint blueprint;
    FillExampleData(blueprint);

    {
        blueprint.MoveCratesAsStack({ 1,1,0 });
        EXPECT_EQ(GetTopRow(blueprint), "DCP");
    }

    {
        blueprint.MoveCratesAsStack({ 3,0,2 });
        EXPECT_EQ(GetTopRow(blueprint), "CD");
    }

    {
        blueprint.MoveCratesAsStack({ 2,1,0 });
        EXPECT_EQ(GetTopRow(blueprint), "CD");
    }

    {
        blueprint.MoveCratesAsStack({ 1,0,1 });
        EXPECT_EQ(GetTopRow(blueprint), "MCD");
    }
}

