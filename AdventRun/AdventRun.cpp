// System
#include <fstream>
#include <iostream>
#include <span>

// AdventLib
#include <DayOne.h>

//------------------------------------------------------------------------------
// Local Declarations
namespace
{
    enum class CommandLineArgs : unsigned int
    {
        File = 1,
        ExpectedCount
    };

    class CommandLineParser
    {
    public:
        explicit CommandLineParser(const std::span<char*> &args);
      
        std::ifstream mFile;
    };

    // int ParseCommandLine(int argc, char** argv);


    //------------------------------------------------------------------------------
    // Puzzles
    void DoDayOne();

}

int main(int argc, char** argv) 
{
    
  //  return ParseCommandLine(argc, argv);
    (void)argc;
    (void)argv;

    DoDayOne();

    return 0;
}

namespace
{
    //------------------------------------------------------------------------------
    // CommandLineParser Implementation
    CommandLineParser::CommandLineParser(const std::span<char*>& args)
        : mFile(args[static_cast<size_t>(CommandLineArgs::File)])
    {

    }
    
    //------------------------------------------------------------------------------
/*
    int ParseCommandLine(int argc, char** argv)
    {
        auto args = std::span(argv, static_cast<size_t>(argc));

        if (args.size() != static_cast<size_t>(CommandLineArgs::ExpectedCount))
        {
            std::cerr << "This program expects one parameter that is the input file to read.\n";
            return 1;
        }

        CommandLineParser parser(args);

        if (!parser.mFile.is_open())
        {
            std::cerr << "Failed to open file.\n";
            return 1;
        }

        return 0;
    }
*/

    //------------------------------------------------------------------------------
    // DoDayOne
    void DoDayOne()
    { 
        const std::string fileName = R"(T:\dev\Advent\AdventLib\DayOne\input.txt)";
        std::ifstream file(fileName);

        if (!file.is_open())
        {
            std::cerr << "Failed to open file.\n";
            return;
        }

        DayOne::Puzzle puzzle;
        puzzle.DoPuzzle(file);
    }

}