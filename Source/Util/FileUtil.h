#ifndef FileUtil_H_INCLUDED
#define FileUtil_H_INCLUDED

#include <vector>
#include <string>

std::string getFileContents(const std::string& filePath);

std::vector<std::string> getFileNamesFromFolder     (const std::string& folderName);
std::vector<std::string> getFolderNamesFromFolder   (const std::string& folderName);


#endif // FileUtil_H_INCLUDED
