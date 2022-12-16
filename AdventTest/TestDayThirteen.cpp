
#include "pch.h"
/*
// Advent Lib
#include <AdventDays/DayThirteen.h>


TEST(DayThirteen, TestPartOneExample1)
{
    using namespace DayThirteen2022;

    / *
[1,1,3,1,1]
[1,1,5,1,1]
    * /
    PacketData leftPacket;
    leftPacket.AddPacket(PacketData(1));
    leftPacket.AddPacket(PacketData(1));
    leftPacket.AddPacket(PacketData(3));
    leftPacket.AddPacket(PacketData(1));
    leftPacket.AddPacket(PacketData(1));

    PacketData rightPacket;
    rightPacket.AddPacket(PacketData(1));
    rightPacket.AddPacket(PacketData(1));
    rightPacket.AddPacket(PacketData(5));
    rightPacket.AddPacket(PacketData(1));
    rightPacket.AddPacket(PacketData(1));

 //   EXPECT_EQ(ComparePackets(leftPacket, rightPacket), CompareResult::Right);
}

TEST(DayThirteen, TestPartOneExample2)
{
    using namespace DayThirteen2022;
/ *
[[1],[2,3,4]]
[[1],4]
* /
    PacketData topPacket;

    {
        PacketData firstTopPacket;
        firstTopPacket.AddPacket(PacketData(1));
        topPacket.AddPacket(firstTopPacket);
    }
    {
        PacketData secondTopPacket;
        secondTopPacket.AddPacket(PacketData(2));
        secondTopPacket.AddPacket(PacketData(3));
        secondTopPacket.AddPacket(PacketData(4));
        topPacket.AddPacket(secondTopPacket);
    }


    PacketData bottomPacket;
    {
        PacketData firstBottomPacket;
        firstBottomPacket.AddPacket(PacketData(1));
        bottomPacket.AddPacket(firstBottomPacket);
    }
    bottomPacket.AddPacket(PacketData(4));

 //   EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Right);
}

TEST(DayThirteen, TestPartOneExample3)
{
    / *
[9]
[[8,7,6]]
* /
    using namespace DayThirteen2022;

    PacketData topPacket;
    topPacket.AddPacket(PacketData(9));

    PacketData bottomPacket;
    {
        PacketData bottomFirst;
        bottomFirst.AddPacket(PacketData(8));
        bottomFirst.AddPacket(PacketData(7));
        bottomFirst.AddPacket(PacketData(6));
        bottomPacket.AddPacket(bottomFirst);
    }

    EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Wrong);

}

TEST(DayThirteen, TestPartOneExample4)
{/ *
    [[4, 4], 4, 4]
    [[4, 4], 4, 4, 4]* /

    using namespace DayThirteen2022;
    PacketData topPacket;

    {
        PacketData topfirst;
        topfirst.AddPacket(PacketData(4));
        topfirst.AddPacket(PacketData(4));
        topPacket.AddPacket(topfirst);
    }

    topPacket.AddPacket(PacketData(4));
    topPacket.AddPacket(PacketData(4));

    PacketData bottomPacket;
    {
        PacketData bottomFirst;
        bottomFirst.AddPacket(PacketData(4));
        bottomFirst.AddPacket(PacketData(4));
        bottomPacket.AddPacket(bottomFirst);
    }

    bottomPacket.AddPacket(PacketData(4));
    bottomPacket.AddPacket(PacketData(4));
    bottomPacket.AddPacket(PacketData(4));

  //  EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Right);

}

TEST(DayThirteen, TestPartOneExample5)
{
    using namespace DayThirteen2022;
  / * [7, 7, 7, 7]
    [7, 7, 7]
    * /
    PacketData topPacket;
    topPacket.AddPacket(PacketData(7));
    topPacket.AddPacket(PacketData(7));
    topPacket.AddPacket(PacketData(7));
    topPacket.AddPacket(PacketData(7));

    PacketData bottomPacket;
    bottomPacket.AddPacket(PacketData(7));
    bottomPacket.AddPacket(PacketData(7));
    bottomPacket.AddPacket(PacketData(7));

    EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Wrong);

}

TEST(DayThirteen, TestPartOneExample6)
{
    / *
    []
[3]
* /


    using namespace DayThirteen2022;
    PacketData topPacket;
    PacketData bottomPacket;
    bottomPacket.AddPacket(PacketData(3));
    //EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Right);

}

TEST(DayThirteen, TestPartOneExample7)
{
    / *
[[[]]]
[[]]
* /


    using namespace DayThirteen2022;
    PacketData topPacket;
    {
        PacketData topInnerPacket;
        topInnerPacket.AddPacket(PacketData());
        topPacket.AddPacket(topInnerPacket);
    }

    PacketData bottomPacket;
    bottomPacket.AddPacket(PacketData());

    EXPECT_EQ(ComparePackets(topPacket, bottomPacket), CompareResult::Wrong);

}*/