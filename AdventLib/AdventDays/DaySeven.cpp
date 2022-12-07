#include "pch.h"
#include "DaySeven.h"

// AdventLib
#include <Utilities/StringUtils.h>

/*
User commands start with "$"
cd <dir>  
cd ..
cd /
ls
____
contents look like:
dir <name>
<filesize> <fileName>


Find all of the directories with a total size of at most 100000. 
What is the sum of the total sizes of those directories?
*/

namespace DaySeven
{
    //------------------------------------------------------------------------------
    // Data Model
    
    //------------------------------------------------------------------------------
    // Directory Implementation
     Directory::Directory(Directory* parentdir)
         : mParentDirectory(parentdir)
    {

    }

     //------------------------------------------------------------------------------
     void Directory::AddFile(const std::string& fileName, size_t fileSize)
     {
         mFiles.emplace_back(fileName, fileSize );
         SizeIncrease(fileSize);
     }

     //------------------------------------------------------------------------------
     void Directory::SizeIncrease(size_t fileSize)
     {
         mTotalSize += fileSize;
         if (mParentDirectory != nullptr)
         {
             mParentDirectory->SizeIncrease(fileSize);
         }
     }
     //------------------------------------------------------------------------------
     void Directory::AddDirectory(const std::string& directoryName)
     {
         mDirectories.emplace(directoryName, Directory(this));
     }

     //------------------------------------------------------------------------------
     Directory& Directory::ChangeDir(const std::string& changeDir)
     {
         static constexpr std::string_view kPrevCommand = "..";

         if (changeDir == kPrevCommand)
         {
             assert(mParentDirectory);
             return *mParentDirectory;
         }

         return mDirectories[changeDir];
     }

     //------------------------------------------------------------------------------
     Directory& Terminal::ChangeDir(const std::string& changeDir)
     {
         static constexpr std::string_view kRootDir = "/";

         if (changeDir == kRootDir)
         {
             mCurrentDirectory = &mRootDirectory;
         }
         else
         {
             mCurrentDirectory = &mCurrentDirectory->ChangeDir(changeDir);
         }

         assert(mCurrentDirectory);
         return *mCurrentDirectory;
     }

     size_t GetSumSizeRecurse(const Directory& currDir, size_t maxSize)
     {
         size_t goalSum = 0;

         {
             const size_t totalSize = currDir.GetTotalSize();

             if (totalSize <= maxSize)
             {
                 goalSum += totalSize;
             }
         }

         for (const auto& [name, dir] : currDir.GetSubDirs())
         {
             goalSum += GetSumSizeRecurse(dir, maxSize);
         }
         return goalSum;
     }

     //------------------------------------------------------------------------------
     size_t Terminal::GetSumSize(size_t maxSize) const
     {
         return GetSumSizeRecurse(mRootDirectory, maxSize);
     }

     static constexpr std::string_view kCommandToken = "$";
     static constexpr std::string_view kChangeDirCommand = "cd";
     static constexpr std::string_view kDirToken = "dir";

     //------------------------------------------------------------------------------
     void ParseFileSystem(const std::string& filename, Terminal& terminal)
     {
         Directory* currDir = nullptr;

         auto input = StringUtils::SplitFile(filename);

         for (const auto& line : input)
         {
             const auto& tokens = StringUtils::SplitString<std::string>(line, " ");

             assert(!tokens.empty());

             if (tokens.at(0) == kCommandToken)
             {
                 assert(tokens.size() >= 2);
                 if (tokens.at(1) == kChangeDirCommand)
                 {
                     assert(tokens.size() == 3);
                     currDir = &terminal.ChangeDir(tokens.at(2));
                 }
             }
             else if (tokens.at(0) == kDirToken)
             {
                 assert(currDir);
                 assert(tokens.size() == 2);
                 currDir->AddDirectory(tokens.at(1));
             }
             else
             {
                 // add file
                 assert(currDir);
                 assert(tokens.size() == 2);
                 currDir->AddFile(tokens.at(1), std::stoi(tokens.at(0)));
             }
         }
     }

    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {

        Terminal terminal;
        ParseFileSystem(filename, terminal);
        
        static constexpr size_t partOneMaxSize = 100000;
        const size_t totalSize = terminal.GetSumSize(partOneMaxSize);

        std::cout << "The total sum of directories under " << partOneMaxSize << " is: " << totalSize << std::endl;
        return totalSize;
    }

    //------------------------------------------------------------------------------
    // Part Two


    void FindFreeSpaceRecursive(const Directory& currDir, size_t spaceNeeded, size_t &outLowest)
    {

        {
            const size_t totalSize = currDir.GetTotalSize();

            if (totalSize >= spaceNeeded 
                && totalSize < outLowest)
            {
                outLowest = totalSize;
            }
        }

        for (const auto& [name, dir] : currDir.GetSubDirs())
        {
            FindFreeSpaceRecursive(dir, spaceNeeded, outLowest);
        }
    }

    size_t Terminal::FindFreeSpace(size_t desiredSpace) const
    {
        static constexpr size_t kTotalSpace = 70000000;
        const size_t unusedSpace = kTotalSpace - mRootDirectory.GetTotalSize();
        assert(desiredSpace > unusedSpace);

        const size_t spaceNeeded = desiredSpace - unusedSpace;
        size_t lowestSize = std::numeric_limits<size_t>::max();
        FindFreeSpaceRecursive(mRootDirectory, spaceNeeded, lowestSize);

        return lowestSize;

    }

    std::any DoPartTwo(const std::string& filename)
    {
        Terminal terminal;
        ParseFileSystem(filename, terminal);

        static constexpr size_t kFreeSpaceNeeded = 30000000;
        const size_t minSize = terminal.FindFreeSpace(kFreeSpaceNeeded);

        std::cout << "Min Size Dir to Delete: " << minSize << std::endl;

        return minSize;
    }
}