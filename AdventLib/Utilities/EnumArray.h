#pragma once
// System
#include <array>

//------------------------------------------------------------------------------
template<typename EnumClass, typename T, EnumClass _First = static_cast<EnumClass>(0), EnumClass _Last =  EnumClass::Last >
class EnumArray
{
    static_assert(_Last >= _First);
    static constexpr size_t kArraySize = (static_cast<size_t>(_Last) - static_cast<size_t>(_First)) + 1;
    
public:
    using DataType = std::array<T, kArraySize>;
   
    constexpr EnumArray() = default;
    explicit constexpr EnumArray(DataType&& init)
        : mData(init)
    {}

    //------------------------------------------------------------------------------
    constexpr T& at(EnumClass idx)
    {
        const auto dataIdx = (static_cast<size_t>(idx) - static_cast<size_t>(_First));
        assert(dataIdx >= 0 && dataIdx < kArraySize);

        return mData.at(dataIdx);
    }

    constexpr const T& at(EnumClass idx) const
    {
        const auto dataIdx = (static_cast<size_t>(idx) - static_cast<size_t>(_First));

        assert(dataIdx >= 0 && dataIdx < kArraySize);

        return mData.at(dataIdx);
    }

    constexpr T& operator[](EnumClass idx)
    {
        return at(idx);
    }

    constexpr const T& operator[](EnumClass idx) const
    {
        return at(idx);
    }

    //------------------------------------------------------------------------------
    //  Iterators
    typename DataType::iterator begin() noexcept { return mData.begin(); }
    typename DataType::iterator end() noexcept { return mData.end(); }
    typename DataType::const_iterator begin() const noexcept { return mData.begin(); }
    typename DataType::const_iterator end() const noexcept { return mData.end(); }
    typename DataType::const_iterator cbegin() const noexcept { return mData.cbegin(); }
    typename DataType::const_iterator cend() const noexcept { return mData.cend(); }
    typename DataType::reverse_iterator rbegin() noexcept { return mData.rbegin(); }
    typename DataType::reverse_iterator rend() noexcept { return mData.rend(); }
    typename DataType::const_reverse_iterator rbegin() const noexcept { return mData.rbegin(); }
    typename DataType::const_reverse_iterator rend() const noexcept { return mData.rend(); }
    typename DataType::const_reverse_iterator crbegin() const noexcept { return mData.crbegin(); }
    typename DataType::const_reverse_iterator crend() const noexcept { return mData.crend(); }

private:
    DataType mData;
};