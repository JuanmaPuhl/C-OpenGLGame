#include "FileManager.h"

FileManager::FileManager()
{

}

FileManager::~FileManager()
{

}

std::string FileManager::readFile(std::string& dir)
{
  std::ifstream file{dir};
  std::string const fileContent = static_cast<std::ostringstream&>
      (std::ostringstream{} << file.rdbuf()).str();
  return fileContent;
}
