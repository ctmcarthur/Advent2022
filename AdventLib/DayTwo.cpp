#include "pch.h"

#include <Utilities/Input.h>

// system
#include <array>
#include <iostream>
#include <unordered_map>


namespace DayTwo
{
    enum class Hand : uint32_t
    {
        ROCK = 0,
        PAPER,
        SCISSORS,
    };

    enum class GameResult : uint32_t
    {
        WIN = 0,
        LOSE,
        DRAW,
    };

    constexpr size_t kArraySizes = 3;

    constexpr std::array<uint32_t, kArraySizes>
        kHandPoints =
    {
        1, // ROCK
        2, // PAPER
        3  // SCISSORS
    };

    constexpr std::array<uint32_t, kArraySizes>
        kResultPoints =
    {
        6, // WIN
        0, // Lose
        3 // Draw
    };

    const std::unordered_map<char, GameResult> kMyResultDecoder =
    {
        {'X', GameResult::LOSE}, // Lose
        {'Y', GameResult::DRAW},// Draw
        {'Z', GameResult::WIN} // Win
    };

    constexpr std::array<std::array<Hand, kArraySizes>, kArraySizes> kHandToGetResult =
    {{
        // ROCK
        {{
            Hand::PAPER,    // Win
            Hand::SCISSORS, // Lose
            Hand::ROCK      // Draw
        }},
        // PAPER
        {{
            Hand::SCISSORS,  // Win
            Hand::ROCK,      // Lose
            Hand::PAPER      // Draw
        }},
        // SCISSORS
        {{
            Hand::ROCK,      // Win
            Hand::PAPER,     // Lose
            Hand::SCISSORS   // Draw
        }},
    }};

    const std::unordered_map<char, Hand> kElfHandDecoder =
    {
        {'A', Hand::ROCK},
        {'B', Hand::PAPER},
        {'C', Hand::SCISSORS}
    };

    const std::unordered_map<char, Hand> kMyHandDecoder =
    {
        {'X', Hand::ROCK},
        {'Y', Hand::PAPER},
        {'Z', Hand::SCISSORS}
    };

    GameResult CalculateResult(Hand myHand, Hand elfHand)
    {
        if (myHand == elfHand)
        {
            return GameResult::DRAW;
        }

        if (myHand == Hand::ROCK)
        {
            return elfHand == Hand::SCISSORS ? GameResult::WIN : GameResult::LOSE;
        }

        if (myHand == Hand::PAPER)
        {
            return elfHand == Hand::ROCK ? GameResult::WIN : GameResult::LOSE;
        }

        // Scissors
        return elfHand == Hand::PAPER ? GameResult::WIN : GameResult::LOSE;
    }

    uint32_t CalculatePoints(Hand myHand, Hand elfHand)
    {
        const GameResult gameResult = CalculateResult(myHand, elfHand);

        return kHandPoints.at(static_cast<size_t>(myHand))
               + kResultPoints.at(static_cast<size_t>(gameResult));
    }

    constexpr size_t kIdxElfCode = 0;
    constexpr size_t kIdxMyCode = 2;

    //------------------------------------------------------------------------------
    void DoPartOne(const std::string& filename)
    {
        const auto input = Utilities::ReadAllLinesInFile(filename);
        uint32_t score = 0;
        for (const auto& line : input)
        {
           const Hand myHand = kMyHandDecoder.at(line[kIdxMyCode]);
           const Hand elfHand = kElfHandDecoder.at(line[kIdxElfCode]);
           score += CalculatePoints(myHand, elfHand);    
        }

        std::cout << "I scored " << score << " points!" << std::endl;
    }


    //------------------------------------------------------------------------------
    void DoPartTwo(const std::string& filename)
    {
        const auto input = Utilities::ReadAllLinesInFile(filename);
        uint32_t score = 0;
        for (const auto& line : input)
        {
            const GameResult myResult = kMyResultDecoder.find(line[kIdxMyCode])->second;
            const Hand elfHand = kElfHandDecoder.find(line[kIdxElfCode])->second;
            
            const Hand myHand = kHandToGetResult.at(static_cast<size_t>(elfHand))
                .at(static_cast<size_t>(myResult));
            
            score += CalculatePoints(myHand, elfHand);
        }

        std::cout << "I scored " << score << " points!" << std::endl;
    }
}

