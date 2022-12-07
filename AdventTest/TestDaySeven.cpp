#include "pch.h"

// Advent Lib
#include <AdventDays/DaySeven.h>
// system

//------------------------------------------------------------------------------
// Test Helpers

namespace
{}

TEST(DaySeven, TestPartOneExamples) 
{
    using namespace DaySeven;
    //   EXPECT_EQ(blueprint.GetTopRow(), "NDP");
    Terminal terminal;

    Directory* curDir = &terminal.ChangeDir("/");

    curDir->AddDirectory("a");
    curDir->AddFile("b", 14848514);
    curDir->AddFile("c", 8504156);
    curDir->AddDirectory("d");

    curDir = &terminal.ChangeDir("a");

    curDir->AddDirectory("e");
    curDir->AddFile("c", 29116);
    curDir->AddFile("c", 2557);
    curDir->AddFile("c", 62596);

    curDir = &terminal.ChangeDir("e");

    curDir->AddFile("c", 584);


    curDir = &terminal.ChangeDir("..");
    curDir = &terminal.ChangeDir("..");
    curDir = &terminal.ChangeDir("d");

    curDir->AddFile("c", 4060174);
    curDir->AddFile("c", 8033020);
    curDir->AddFile("c", 5626152);
    curDir->AddFile("c", 7214296);

    EXPECT_EQ(terminal.GetSumSize(100000), 95437);
}
