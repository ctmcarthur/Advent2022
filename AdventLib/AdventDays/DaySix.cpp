#include "pch.h"
#include "DaySix.h"

// AdventLib
#include <Utilities/StringUtils.h>


/*
*problem:
get a series of characters.
which index has the previous 4 characters as unique?
*/

/*
* alg
every time, check the last 4 against a bitfield
*/
namespace DaySix
{
    bool AllCharactersUnique(std::string_view code)
    {
        constexpr size_t kLettersInAlphabet = 26;
        constexpr char kFirstLetter = 'a';

        std::bitset<kLettersInAlphabet> letters{};

        for (char character : code)
        {
            assert(islower(character));
            letters.set(static_cast<size_t>(character) - kFirstLetter);
        }

        return letters.count() == code.size();
    }

    size_t FindFirstKeyIdx(const std::string& input, uint32_t keySize)
    {
        assert(keySize > 0 && input.size() >= keySize);

        const auto endIter = input.end();
        for (auto iter = std::next(input.begin(), keySize); 
            iter != endIter; 
            ++iter)
        {
            auto keyStart = std::prev(iter, keySize);
            if (AllCharactersUnique({ keyStart.operator->(), keySize }))
            {
                return std::distance(input.begin(), iter);
            }
        }

        assert(false);
        return 0;
    }

    //------------------------------------------------------------------------------
    std::any DoPartOne(const std::string& filename)
    {
        std::string input;
        std::getline(std::ifstream(filename), input);

        constexpr uint32_t keySize = 4;
        auto keyIdx = FindFirstKeyIdx(input, keySize);
        std::cout << "Index of Decoding Key: " << keyIdx << std::endl;

        return keyIdx;
    }

    //------------------------------------------------------------------------------
    std::any DoPartTwo(const std::string& filename)
    {
        std::string input;
        std::getline(std::ifstream(filename), input);

        constexpr uint32_t keySize = 14;
        auto keyIdx = FindFirstKeyIdx(input, keySize);
        std::cout << "Index of Decoding Key: " << keyIdx << std::endl;

        return keyIdx;
    }
}