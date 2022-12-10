#include "pch.h"

// Advent Lib
#include <AdventDays/DayTen.h>


TEST(DayTen, TestShortExample)
{
    using namespace DayTen;

    CRT crt;
    crt.PushNoop();
    crt.PushAdd(3);
    crt.PushAdd(-5);

    EXPECT_EQ(crt.GetValue(1), 1);

    EXPECT_EQ(crt.GetValue(2), 1);

    EXPECT_EQ(crt.GetValue(3), 1);

    EXPECT_EQ(crt.GetValue(4), 4);

    EXPECT_EQ(crt.GetValue(5), 4);
    EXPECT_EQ(crt.GetValue(6), -1);

}
