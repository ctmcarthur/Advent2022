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
     void Directory::AddFile(std::string&& fileName, size_t fileSize)
     {
         mFiles.emplace_back(std::move(fileName), fileSize );
         SizeIncrease(fileSize);
     }

     //------------------------------------------------------------------------------
     void Directory::SizeIncrease(size_t fileSize)
     {
         mTotalSize += fileSize;
         if (mParentDirectory)
         {
             mParentDirectory->SizeIncrease(fileSize);
         }
     }
     //------------------------------------------------------------------------------
     void Directory::AddDirectory(std::string&& directoryName)
     {
         mDirectories.emplace(std::move(directoryName), Directory(this));
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

    //------------------------------------------------------------------------------
    // Part One
    std::any DoPartOne(const std::string& filename)
    {
        uint32_t ret = 0;

        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        return ret;
    }

    //------------------------------------------------------------------------------
    // Part Two
    std::any DoPartTwo(const std::string& filename)
    {
        uint32_t ret = 0;

        auto input = StringUtils::SplitFile(filename);

        for (const auto& line : input)
        {
            (void)line;
        }

        return ret;
    }
}