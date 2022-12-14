// AdventLib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "AdventDay.h"
#include "AdventLib.h"

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define FWD_DECLARE_DAY(NAMESPACE) \
namespace NAMESPACE\
{\
    PuzzleSolution DoPartOne(const std::filesystem::path& filename);\
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename);\
}

#define REGISTER_DAY(NAMESPACE, DAY, YEAR)  static const AdventDay NAMESPACE(DAY, YEAR, { &NAMESPACE::DoPartOne, &NAMESPACE::DoPartTwo })
// NOLINTEND(cppcoreguidelines-macro-usage)


FWD_DECLARE_DAY(DayOne2022);
FWD_DECLARE_DAY(DayTwo2022);
FWD_DECLARE_DAY(DayThree2022);
FWD_DECLARE_DAY(DayFour2022);
FWD_DECLARE_DAY(DayFive2022);
FWD_DECLARE_DAY(DaySix2022);
FWD_DECLARE_DAY(DaySeven2022);
FWD_DECLARE_DAY(DayEight2022);
FWD_DECLARE_DAY(DayNine2022);
FWD_DECLARE_DAY(DayTen2022);
FWD_DECLARE_DAY(DayEleven2022);
FWD_DECLARE_DAY(DayTwelve2022);
FWD_DECLARE_DAY(DayThirteen2022);
FWD_DECLARE_DAY(DayFourteen2022);
// FWD_DECLARE_DAY(DayFifteen2022);
// FWD_DECLARE_DAY(DaySixteen2022);
// FWD_DECLARE_DAY(DaySeventeen2022);
// FWD_DECLARE_DAY(DayEighteen2022);
// FWD_DECLARE_DAY(DayNineteen2022);
// FWD_DECLARE_DAY(DayTwenty2022);
// FWD_DECLARE_DAY(DayTwentyOne2022);
// FWD_DECLARE_DAY(DayTwentyTwo2022);
// FWD_DECLARE_DAY(DayTwentyThree2022);
// FWD_DECLARE_DAY(DayTwentyFour2022);
// FWD_DECLARE_DAY(DayTwentyFive2022);

namespace Year2022
{
    void RegisterDays()
    {

        REGISTER_DAY(DayOne2022, 1, 2022);
        REGISTER_DAY(DayTwo2022, 2, 2022);
        REGISTER_DAY(DayThree2022, 3, 2022);
        REGISTER_DAY(DayFour2022, 4, 2022);
        REGISTER_DAY(DayFive2022, 5, 2022);
        REGISTER_DAY(DaySix2022, 6, 2022);
        REGISTER_DAY(DaySeven2022, 7, 2022);
        REGISTER_DAY(DayEight2022, 8, 2022);
        REGISTER_DAY(DayNine2022, 9, 2022);
        REGISTER_DAY(DayTen2022, 10, 2022);
        REGISTER_DAY(DayEleven2022, 11, 2022);
        REGISTER_DAY(DayTwelve2022, 12, 2022);
        REGISTER_DAY(DayThirteen2022, 13, 2022);
        REGISTER_DAY(DayFourteen2022, 14, 2022);
//         REGISTER_DAY(DayFifteen2022, 15, 2022);
//         REGISTER_DAY(DaySixteen2022, 16, 2022);
//         REGISTER_DAY(DaySeventeen2022, 17, 2022);
//         REGISTER_DAY(DayEighteen2022, 18, 2022);
//         REGISTER_DAY(DayNineteen2022, 19, 2022);
//         REGISTER_DAY(DayTwenty2022, 20, 2022);
//         REGISTER_DAY(DayTwentyOne2022, 21, 2022);
//         REGISTER_DAY(DayTwentyTwo2022, 22, 2022);
//         REGISTER_DAY(DayTwentyThree2022, 23, 2022);
//         REGISTER_DAY(DayTwentyFour2022, 24, 2022);
//         REGISTER_DAY(DayTwentyFive2022, 25, 2022);
    }
}