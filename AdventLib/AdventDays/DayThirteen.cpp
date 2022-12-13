#include "pch.h"
#include "DayThirteen.h"

// AdventLib
#include <AdventDay.h>
#include <Utilities/StringUtils.h>

namespace DayThirteen2022
{
    
    PacketData::PacketData()
        : mIsList(true)
    {
        mData = PacketList();
    }

    PacketData::PacketData(int32_t value)
        : mIsList(false)
    {
        mData = value;
    }

    PacketData& PacketData::AddPacket(const PacketData& packet)
    {
        if (mIsList == false)
        {
            mData = PacketList();
        }

        mIsList = true;
        
        GetList().push_back(packet);
        return GetList().back();
    }

    int32_t PacketData::GetValue() const
    {
        assert(mIsList == false);
        return std::get<int32_t>(mData);
    }

    const PacketList& PacketData::GetList() const
    {
        assert(mIsList == true);
        return std::get<PacketList>(mData);
    }

    PacketList& PacketData::GetList()
    {
        assert(mIsList == true);
        return std::get<PacketList>(mData);
    }

    class PacketPair
    {
    public:
        PacketData mTopPacket;
        PacketData mBottomPacket;
    };

    CompareResult ComparePackets(const PacketData& firstPacket, const PacketData& secondPacket)
    {
        if (!firstPacket.IsList() && !secondPacket.IsList())
        {
            // return compare ints.
            const auto firstVal = firstPacket.GetValue();
            const auto secondVal = secondPacket.GetValue();

            if (firstVal == secondVal)
            {
                return CompareResult::Unknown;
            }
            
            return (firstVal < secondVal) ? CompareResult::Right : CompareResult::Wrong;
        }

        PacketList firstPlaceholderList;
        PacketList secondPlaceholderList;

        const PacketList* firstList = nullptr;
        const PacketList* secondList = nullptr;

        if (firstPacket.IsList())
        {
            firstList = &firstPacket.GetList();
        }
        else
        {
            firstPlaceholderList.emplace_back(firstPacket.GetValue());
            firstList = &firstPlaceholderList;
        }

        if (secondPacket.IsList())
        {
            secondList = &secondPacket.GetList();
        }
        else
        {
            secondPlaceholderList.emplace_back(secondPacket.GetValue());
            secondList = &secondPlaceholderList;
        }
        
        for (size_t i = 0; i < firstList->size(); ++i)
        {
            if (i >= secondList->size())
            {
                return CompareResult::Wrong;
            }

            const CompareResult result = ComparePackets(firstList->at(i), secondList->at(i));
           
            if (result != CompareResult::Unknown)
            {
                // stop searching if we found an answer.
                return result;
            }

        }

        if (firstList->size() < secondList->size())
        {
            return CompareResult::Right;
        }

        return CompareResult::Unknown;        
    }
    
    class PacketReader
    {
    public:
        size_t SumCorrectPairs() const;
        size_t CountPairsLessThan(const PacketData& comparePacket) const;
        std::vector<std::pair<PacketData, PacketData>> mPackets;
    };

    size_t PacketReader::SumCorrectPairs() const 
    {
        size_t currentIdx = 1; // elves start at one.
        size_t resultSum = 0;

        for (const auto& [firstPacket, secondPacket] : mPackets)
        {
            if (ComparePackets(firstPacket, secondPacket) == CompareResult::Right)
            {
                resultSum += currentIdx;
            }

            ++currentIdx;
        }

        return resultSum;
    }

    size_t PacketReader::CountPairsLessThan(const PacketData& comparePacket) const
    {
        size_t currentCount = 0;
        for (const auto& [firstPacket, secondPacket] : mPackets)
        {
            if (ComparePackets(firstPacket, comparePacket) == CompareResult::Right)
            {
                ++currentCount;
            }

            if (ComparePackets(secondPacket, comparePacket) == CompareResult::Right)
            {
                ++currentCount;
            }
        }


        return currentCount;
    }

    size_t ParsePacketRecurse(PacketData &packet, const std::string& line, size_t startIdx)
    {
        size_t lineIdx = startIdx;
        
        while (lineIdx <= line.size() && line[lineIdx] != ']')
        {
            if (line[lineIdx] == '[')
            {
                PacketData innerPacket;
                lineIdx = ParsePacketRecurse(innerPacket, line, lineIdx+1);
                packet.AddPacket(innerPacket);
                continue;
            }
            
            if (line[lineIdx] == ',')
            {
                lineIdx++;
                continue;
            }

            const size_t endValues = line.find_first_of("[]", lineIdx);
            
            const auto& newValues = StringUtils::SplitString<int32_t>(line.substr(lineIdx, (endValues - lineIdx)), ",");

            for (auto packetValue : newValues)
            {
                packet.AddPacket(PacketData(packetValue));
            }

            lineIdx = endValues;
        }

        ++lineIdx;
        return lineIdx;
    }

    PacketData ParsePacket(const std::string& line)
    {
        assert(line[0] == '[');
        PacketData topPacket;

        ParsePacketRecurse(topPacket, line, 1);

        return topPacket;
    }

    PacketReader ParsePackets(const std::filesystem::path& filename)
    {
        PacketReader packetReader;
        const auto input = StringUtils::SplitFile(filename);

        for (size_t i = 0; i < input.size(); i += 3)
        {
            packetReader.mPackets.emplace_back(
                ParsePacket(input[i]), ParsePacket(input[i + 1]));
        }

        return packetReader;

    }
    //------------------------------------------------------------------------------
    // Part One
    PuzzleSolution DoPartOne(const std::filesystem::path& filename)
    {
        
        PacketReader packetReader = ParsePackets(filename);

        const size_t correctPairSum = packetReader.SumCorrectPairs();

        std::cout << "The Sum of Correct Pairs Is: " << correctPairSum << "\n";

        return { {correctPairSum}, {&CompareAny<size_t>} };

    }

    //------------------------------------------------------------------------------
    // Part Two
    PuzzleSolution DoPartTwo(const std::filesystem::path& filename)
    {
        PacketReader packetReader = ParsePackets(filename);
        
        PacketData packet2; // build packet [[2]]
        {
            PacketData innerPacket(PacketData(2));
            packet2.AddPacket(innerPacket);
        }

        PacketData packet6; // build packet [[6]] 
        {
            PacketData innerPacket(PacketData(6));
            packet6.AddPacket(innerPacket);
        }

        const size_t packet2Idx = packetReader.CountPairsLessThan(packet2) + 1;
        const size_t packet6Idx = packetReader.CountPairsLessThan(packet6) + 2; // elf indicing + packet 2
        const size_t decorderKey = packet2Idx * packet6Idx;

        std::cout << "The Decoder Key IS: " << decorderKey << "\n";

        return { {decorderKey}, {&CompareAny<size_t>} };

    }
}