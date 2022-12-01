#include "pch.h"

#include <AdventLib.h>

TEST(TestCaseName, TestName) 
{
    const int meow = 10;
   
  EXPECT_EQ(fnAdventLib(meow), meow);
  EXPECT_TRUE(true);
}