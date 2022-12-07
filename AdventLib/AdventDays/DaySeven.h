#pragma once

namespace DaySeven
{
    class File
    {
    public:
        File() = default;
        File(std::string&& fileName, size_t fileSize)
            : mFileName(std::move(fileName))
            , mFileSize(fileSize)
        {

        }

        std::string mFileName;
        size_t mFileSize = 0;
    };

    class Directory;
    using DirectoryList = std::unordered_map<std::string, Directory>;

    class Directory
    {
    public:
        explicit Directory(Directory* parentdir);
        Directory() = default;
        Directory(Directory&& directory) = default;
        Directory& operator=(Directory&& directory) = default;

        void AddFile(std::string&& fileName, size_t fileSize);
        void SizeIncrease(size_t fileSize);
        void AddDirectory(std::string&& directoryName);
        Directory& ChangeDir(const std::string& changeDir);

        size_t GetTotalSize() const { return mTotalSize; }
        const DirectoryList& GetSubDirs() const { return mDirectories; }


    private:

        std::vector<File> mFiles;
        DirectoryList mDirectories;

        // mutable data.
        Directory* mParentDirectory = nullptr;
        size_t mTotalSize = 0;
    };

    class Terminal
    {
    public:
        Directory& ChangeDir(const std::string& changeDir);
        size_t GetSumSize(size_t maxSize) const; 

    private:

        Directory mRootDirectory;
        Directory* mCurrentDirectory = &mRootDirectory;
    };
}