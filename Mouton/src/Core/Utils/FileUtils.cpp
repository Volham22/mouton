#include "FileUtils.h"


namespace Mouton::Utils
{

    DirectoryItem::DirectoryItem(const std::string& filepath, bool isDir)
        : m_Path(filepath), m_IsDir(isDir)
    {
    }

    Directory::Directory(const std::string& dirPath)
        : m_DirPath(dirPath)
    {
    }

} // namespace Mouton::Utils

