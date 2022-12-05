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
    EXPECT_EQ(blueprint.GetTopRow(), "NDP");
}

TEST(DayFive, PartOneBoxMoving)
{
    using namespace DayFive;
    SupplyStacksBlueprint blueprint;
    FillExampleData(blueprint);
    const auto craneVersion = CraneVersion::CRANE_9000;

    {
        blueprint.ExecuteCraneInstruction({ 1,1,0 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "DCP");
    }

    {
        blueprint.ExecuteCraneInstruction({ 3,0,2 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "CZ");
    }

    {
        blueprint.ExecuteCraneInstruction({ 2,1,0 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "MZ");
    }

    {
        blueprint.ExecuteCraneInstruction({ 1,0,1 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "CMZ");
    }
}

TEST(DayFive, PartTwoBoxMoving)
{
    using namespace DayFive;
    SupplyStacksBlueprint blueprint;
    FillExampleData(blueprint);

    const auto craneVersion = CraneVersion::CRANE_9001;

    {
        blueprint.ExecuteCraneInstruction({ 1,1,0 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "DCP");
    }

    {
        blueprint.ExecuteCraneInstruction({ 3,0,2 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "CD");
    }

    {
        blueprint.ExecuteCraneInstruction({ 2,1,0 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "CD");
    }

    {
        blueprint.ExecuteCraneInstruction({ 1,0,1 }, craneVersion);
        EXPECT_EQ(blueprint.GetTopRow(), "MCD");
    }
}

