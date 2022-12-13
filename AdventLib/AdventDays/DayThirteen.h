#pragma once

namespace DayThirteen2022
{
    class PacketData;
    using PacketList = std::vector<PacketData>;

    class PacketData
    {
    public:
        PacketData();
        explicit PacketData(int32_t value);
        PacketData& AddPacket(const PacketData& packet);

        int32_t GetValue() const;
        const PacketList& GetList() const;
        bool IsList() const { return mIsList; }

    private:
        PacketList& GetList();
        bool mIsList;
        std::variant <int32_t, PacketList> mData;
    };

    enum class CompareResult : int32_t
    {
        Wrong,
        Right,
        Unknown
    };

    CompareResult ComparePackets(const PacketData& firstPacket, const PacketData& secondPacket);
}