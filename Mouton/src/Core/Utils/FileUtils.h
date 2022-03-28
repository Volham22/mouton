#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "MoutonPch.h"

#include <filesystem>

namespace Mouton::Utils {

    class DirectoryItem
    {
      public:
        DirectoryItem() = delete;
        DirectoryItem(const std::string& path, bool isDir = false);

        bool IsDirectory() const { return m_IsDir; };
        const std::string& GetPath() const { return m_Path; };

      private:
        std::string m_Path;
        bool m_IsDir;
    };

    class Directory
    {
      public:
        Directory() = delete;
        Directory(const std::string& dirPath);

        const std::string& GetPath() const { return m_DirPath; };

        template<bool Recursive = false>
        std::vector<DirectoryItem> GetDirectoryItems() const
        {
            namespace fs = std::filesystem;
            std::vector<DirectoryItem> items;

            if constexpr (Recursive)
            {
                for (const auto& item :
                     fs::recursive_directory_iterator(m_DirPath))
                    items.push_back(
                        DirectoryItem(item.path(), item.is_directory()));
            } else
            {
                for (const auto& item : fs::directory_iterator(m_DirPath))
                    items.push_back(
                        DirectoryItem(item.path(), item.is_directory()));
            }

            return items;
        }

        // TODO: Add file and directory creation

      private:
        std::string m_DirPath;
    };

} // namespace Mouton::Utils

#endif