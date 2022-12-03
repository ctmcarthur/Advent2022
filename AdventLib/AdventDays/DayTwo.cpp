#include "pch.h"

#include <Utilities/Input.h>

// system
#include <any>
#include <array>
#include <iostream>
#include <unordered_map>


namespace DayTwo
{
    //------------------------------------------------------------------------------
    // Game Enums

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

    //------------------------------------------------------------------------------
    // Lookup Tables
    constexpr size_t kArraySizes = 3;

    //------------------------------------------------------------------------------
    // Points for playing a Hand
    constexpr std::array<uint32_t, kArraySizes>
        kHandPoints =
    {
        1, // ROCK
        2, // PAPER
        3  // SCISSORS
    };

    //------------------------------------------------------------------------------
    // Points for game Result
    constexpr std::array<uint32_t, kArraySizes>
        kResultPoints =
    {
        6, // WIN
        0, // Lose
        3 // Draw
    };

    //------------------------------------------------------------------------------
    // Decoding Elf's hand from Data
    constexpr size_t kIdxElfCode = 0;

    const std::unordered_map<char, Hand> kElfHandDecoder =
    {
        {'A', Hand::ROCK},
        {'B', Hand::PAPER},
        {'C', Hand::SCISSORS}
    };

    //------------------------------------------------------------------------------
    // Decoding My hand from Data

    constexpr size_t kIdxMyCode = 2;

    const std::unordered_map<char, Hand> kMyHandDecoder =
    {
        {'X', Hand::ROCK},
        {'Y', Hand::PAPER},
        {'Z', Hand::SCISSORS}
    };

    //------------------------------------------------------------------------------
    // The Rules of RPS
    constexpr std::array<std::array<GameResult, kArraySizes>, kArraySizes> kCalculateGameResult =
    { {
        // ROCK
        {{
            GameResult::DRAW,   // ROCK
            GameResult::LOSE,   // PAPER
            GameResult::WIN     // SCISSORS
        }},
        // PAPER
        {{
            GameResult::WIN,    // ROCK
            GameResult::DRAW,   // PAPER
            GameResult::LOSE    // SCISSORS
        }},
        // SCISSORS
        {{
            GameResult::LOSE,   // ROCK
            GameResult::WIN,    // PAPER
            GameResult::DRAW   // SCISSORS
        }},
    } };

    //------------------------------------------------------------------------------
    // Helper Functions
    constexpr GameResult CalculateResult(Hand myHand, Hand elfHand)
    {
       return kCalculateGameResult.at(static_cast<size_t>(myHand))
           .at(static_cast<size_t>(elfHand));
    }

    //------------------------------------------------------------------------------
    constexpr uint32_t CalculatePoints(Hand myHand, Hand elfHand)
    {
        const GameResult gameResult = CalculateResult(myHand, elfHand);

        return kHandPoints.at(static_cast<size_t>(myHand))
               + kResultPoints.at(static_cast<size_t>(gameResult));
    }

 

    //------------------------------------------------------------------------------
    // Part 1
    std::any DoPartOne(const std::string& filename)
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
        return score;
    }


     //------------------------------------------------------------------------------
    // Part 2
    
    //------------------------------------------------------------------------------
    // Reverse lookup table for RPS wins from result. 
    constexpr std::array<std::array<Hand, kArraySizes>, kArraySizes> kHandToGetResult =
    { {
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
    } };

    //------------------------------------------------------------------------------
    // decoding my desired result
    const std::unordered_map<char, GameResult> kMyResultDecoder =
    {
        {'X', GameResult::LOSE}, // Lose
        {'Y', GameResult::DRAW},// Draw
        {'Z', GameResult::WIN} // Win
    };

    //------------------------------------------------------------------------------
    std::any DoPartTwo(const std::string& filename)
    {
        const auto input = Utilities::ReadAllLinesInFile(filename);
        uint32_t score = 0;
        for (const auto& line : input)
        {
            const GameResult myResult = kMyResultDecoder.at(line[kIdxMyCode]);
            const Hand elfHand = kElfHandDecoder.at(line[kIdxElfCode]);
            const Hand myHand = kHandToGetResult.at(static_cast<size_t>(elfHand))
                .at(static_cast<size_t>(myResult));
            
            score += CalculatePoints(myHand, elfHand);
        }

        std::cout << "I scored " << score << " points!" << std::endl;

        return score;
    }
}

