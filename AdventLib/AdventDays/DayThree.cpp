#include "pch.h"

#include <Utilities/StringUtils.h>

// system
#include <cctype>

/*
Each rucksack has 2 compartments
compartments are equal size
every item should only be in one compartment.
one item in each is in two compartments
priority: a-z = 1-26  , A-Z = 27-52

Find the item type that appears in both compartments of each rucksack. 
What is the sum of the priorities of those item types?
*/
namespace DayThree
{
    //------------------------------------------------------------------------------
    // Helpers

    // return the character that is in every rucksack
    constexpr char FindMatchingItem(const std::vector<std::string_view>& rucksacks)
    {
        char foundItem = 0;

        if (!rucksacks.empty())
        {
            for (const char item : rucksacks.front())
            {
                assert(item <= 'z');

                bool matchesAll = true;

                for (auto iter = std::next(rucksacks.begin()); iter != rucksacks.end(); ++iter)
                {
                    const auto nextSack = *iter;

                    if (nextSack.find(item) == std::string::npos)
                    {
                        // did not find it;
                        matchesAll = false;
                        break;
                    }
                }

                if (matchesAll)
                {
                    // found it!
                    break;
                }
            }
        }

        assert(foundItem != 0);
        return foundItem;
    }

    //------------------------------------------------------------------------------
    // a-z = 1-26
    // A-Z = 27-53
    uint32_t GetPriority(char item)
    {
        constexpr uint32_t lowercaseStart = 1;
        constexpr uint32_t uppercaseStart = 27;

        if (islower(item) != 0)
        {
            return (item - 'a') + lowercaseStart;
            
        }

        //upper case
        return (item - 'A') + uppercaseStart;
    }
    
    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        const auto input = StringUtils::SplitFile(filename);
        uint32_t prioritySum = 0;
        for (const auto& rucksack : input)
        {
            // split into two rucksacks:
            assert(!rucksack.empty());
            assert((rucksack.size() % 2) == 0); // must be even
           
            // replace with gsl narrow
            const auto midWayIter =
                rucksack.begin() + static_cast<std::vector<std::string>::difference_type>(rucksack.size() / 2);
            const std::string_view leftSack(rucksack.begin().operator->(), midWayIter - rucksack.begin());
            const std::string_view rightSack(midWayIter.operator->(), rucksack.end() - midWayIter);
          
            /*const auto rucksackSize = rucksack.size() / 2;

            const std::string_view leftSack(&rucksack.at(0), rucksackSize);
            const std::string_view rightSack(&rucksack.at(rucksackSize), rucksackSize);
         */
            const char badlySortedItem = FindMatchingItem({ leftSack, rightSack });
           
            prioritySum += GetPriority(badlySortedItem);
        }

        std::cout << "The Priority Sum is: " << prioritySum;
        return prioritySum;
    }

    //------------------------------------------------------------------------------
    //Part 2
  
    std::any DoPartTwo(const std::string& filename)
    {
        constexpr uint32_t kElfGroupSize = 3;
  
        const auto input = StringUtils::SplitFile(filename);
        uint32_t prioritySum = 0;
        const auto inputSize = input.size();

        for (size_t i = 0; i <= (inputSize - kElfGroupSize); i += kElfGroupSize)
        {
            const char badgeItem = FindMatchingItem({ input[i], input[i + 1], input[i + 2] });
            prioritySum += GetPriority(badgeItem);
        }
        

        std::cout << "The Sum of The " << kElfGroupSize << " Badges is : " << prioritySum;
        return prioritySum;
    }
}
