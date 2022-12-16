#include "pch.h"
#include "DayFifteen.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/Grid.h>
#include <Utilities/Range.h>
#include <Utilities/StringUtils.h>

namespace DayFifteen2022
{
    
   class Sensor
   {
   public:
       GridCoordinate mPosition;
       GridCoordinate mClosestBeacon;
   };

   enum class CellContents
   {
       Unknown,
       Sensor,
       Beacon,
       Empty
   };

   // if my y position is P, and the manhatten distance is M
   // which Y values at 2mil are within that manhatten distance?
   // (M - abs(gy-Y)) = F - if negative do nothing. If Otherwise same X, gY, then x-F and x+f;

   using RowValues = RangeSet;

   void CheckEmptySectors(const Sensor& sensor, int32_t row, RowValues& emptySpots)
   {
       // (M - abs(gy-Y)) = F - if negative do nothing. If Otherwise same X, gY, then x-F and x+f;

       const auto manhattenDistance = sensor.mPosition.ManhattenDistance(sensor.mClosestBeacon);
       const auto goalDistance = manhattenDistance - std::abs(row - sensor.mPosition.y);


       if (goalDistance < 0)
       {
           return;
       }


       emptySpots.InsertRange({ (sensor.mPosition.x - goalDistance), (sensor.mPosition.x + goalDistance) });
   }

   void FillEmptyClamped(const Sensor& sensor, int32_t row, const Range& minMax, RowValues& emptySpots)
   {
       // (M - abs(gy-Y)) = F - if negative do nothing. If Otherwise same X, gY, then x-F and x+f;

       const auto manhattenDistance = sensor.mPosition.ManhattenDistance(sensor.mClosestBeacon);
       const auto goalDistance = manhattenDistance - std::abs(row - sensor.mPosition.y);


       if (goalDistance < 0)
       {
           return;
       }


       emptySpots.InsertRange({ 
           std::clamp((sensor.mPosition.x - goalDistance), minMax.mStart, minMax.mEnd), 
           std::clamp((sensor.mPosition.x + goalDistance), minMax.mStart, minMax.mEnd) });
   }


   uint64_t CalculateEmptyAtRow(const std::vector<Sensor>& mSensors, int32_t row)
   {
       RowValues emptySpots;
       std::unordered_set<int32_t> beaconsOnRow;


       for (const auto& sensor : mSensors)
       {
           CheckEmptySectors(sensor, row, emptySpots);
           if (sensor.mClosestBeacon.y == row)
           {
               beaconsOnRow.insert(sensor.mClosestBeacon.x);
           }
       }

       return CountUniqueValues(emptySpots.GetRanges()) - (beaconsOnRow.size());
   }

   

   GridCoordinate ParseCoordinate(const std::string& line)
   {
       assert(line.size() >= 8);
       assert(line[0] == 'x');

       const size_t commaIdx = line.find_first_of(',');
       GridCoordinate newCoord;
       newCoord.x = std::stoi(line.substr(2, commaIdx-2));
       newCoord.y = std::stoi(line.substr(commaIdx + 4));

       return newCoord;
   }

    Sensor ParseSensor(const std::string& line)
    {
        Sensor newSensor;
        
        static constexpr size_t kFirstXIdx = 10;
        
        const size_t firstSeperator = line.find_first_of(':');
        assert(firstSeperator != std::string::npos);

        newSensor.mPosition = ParseCoordinate(line.substr(kFirstXIdx, (firstSeperator - kFirstXIdx)));
        
        const size_t beaconStart = line.find_last_of('x');
        assert(beaconStart != std::string::npos);

        newSensor.mClosestBeacon = ParseCoordinate(line.substr(beaconStart));

        return newSensor;
    }

    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        std::vector<Sensor> searchArea;

        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            searchArea.push_back(ParseSensor(line));
        }

        static constexpr size_t kExampleSize = 14;
        static constexpr int32_t kExampleGoalRow = 10;
        static constexpr int32_t kInputGoalRow = 2000000;
      
        const int32_t goalRow = (searchArea.size() == kExampleSize) ? kExampleGoalRow : kInputGoalRow;
        const auto emptSpots = CalculateEmptyAtRow(searchArea, goalRow);

        std::cout << "The Number of possible Spots at row: " << goalRow << " is: " << emptSpots  << "\n";

        return { {emptSpots}, {&CompareAny<size_t>} };
    }

    //------------------------------------------------------------------------------
    // Part Two

    class FindBeacon
    {
    public:
        FindBeacon(const std::vector<Sensor>& signals, int32_t maxCoord);
        [[nodiscard]] GridCoordinate GetBeaconLocation();
    private:
        RowValues FillRow(int32_t row);
        const std::vector<Sensor>& mSensors;
        const int32_t mMaxCoord;
        const Range mClamp;

    };

    FindBeacon::FindBeacon(const std::vector<Sensor>& signals, int32_t maxCoord)
        : mSensors(signals)
        , mMaxCoord(maxCoord)
        , mClamp{0, maxCoord}
    {}


    RowValues FindBeacon::FillRow(int32_t row)
    {
        RowValues filledSpots;
        for (const auto& sensor : mSensors)
        {
            FillEmptyClamped(sensor, row, mClamp, filledSpots);
            if (sensor.mClosestBeacon.y == row)
            {
                filledSpots.InsertRange({ sensor.mClosestBeacon.y , sensor.mClosestBeacon.y });
            }
            if (sensor.mPosition.y == row)
            {
                filledSpots.InsertRange({ sensor.mPosition.y , sensor.mPosition.y });
            }
        }

        return filledSpots;
    }

    std::optional<int32_t> FindFirstEmpty(const RowValues& values)
    {
        int32_t lastRange = 0;
        for (const auto& range : values.GetRanges())
        {
            if (range.mStart > lastRange)
            {
                return lastRange;
            }

            lastRange = range.mEnd + 1;
        }

        return {};
    }

    GridCoordinate FindBeacon::GetBeaconLocation()
    {
        for (int32_t i = 0; i < mMaxCoord; ++i)
        {
            const RowValues values = FillRow(i);

            if (auto emptyPos = FindFirstEmpty(values))
            {
                return { *emptyPos, i };
            }
        }

        assert(false);
        return {};
    }

    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        std::vector<Sensor> searchArea;

        const auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            searchArea.push_back(ParseSensor(line));
        }

        static constexpr size_t kExampleSize = 14;
        static constexpr int32_t kExampleGoalRow = 20;
        static constexpr int32_t kInputGoalRow = 4000000;

        const int32_t goalRow = (searchArea.size() == kExampleSize) ? kExampleGoalRow : kInputGoalRow;
        const auto gridCoord = FindBeacon(searchArea, goalRow).GetBeaconLocation();
        
        static constexpr uint64_t kFrequencyMultiplier = 4000000;
        const uint64_t frequency = (static_cast<uint64_t>(gridCoord.x) * kFrequencyMultiplier) + static_cast<uint64_t>(gridCoord.y);
        std::cout << "The Frequency of distress beacon is: " << frequency << "\n";
        return { {frequency}, {&CompareAny<uint32_t>} };
    }
}