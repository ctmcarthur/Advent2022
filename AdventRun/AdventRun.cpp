// System

// AdventLib
#include <AdventCalendar.h>
#include <AdventLib.h>

int main()
{
    AdventCalendar calendar;
    //calendar.DoToday();
    calendar.DoDay(3, { PuzzleSection::PartOne }, PuzzleInputType::RealData);
}