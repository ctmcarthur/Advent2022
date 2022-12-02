#include "pch.h"
#include "AdventCalendar.h"

//------------------------------------------------------------------------------
// local decl
namespace
{

}

//------------------------------------------------------------------------------
// AdventCalender definition

//------------------------------------------------------------------------------
AdventCalendar::AdventCalendar()
{

}

//------------------------------------------------------------------------------
void AdventCalendar::DoToday()
{
    DoDay(2, SectionFlags::PartOne, DataTypeFlags::ExampleData);
}

//------------------------------------------------------------------------------
void AdventCalendar::DoDay(DayId /*day*/, SectionFlags /*sections*/, DataTypeFlags /*dataSrc*/)
{
    
}

//------------------------------------------------------------------------------
void AdventCalendar::DoEveryDay(SectionFlags sections, DataTypeFlags dataSrc)
{
    for (DayId day = 0; day < mDays.size(); ++day)
    {
        DoDay(day, sections, dataSrc);
    }
}

//------------------------------------------------------------------------------
// local definitions
namespace
{

}