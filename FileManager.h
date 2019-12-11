#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_
#include <string>
#include <fstream>
#include <sstream>
class FileManager
{
public:
  FileManager();
  ~FileManager();
  std::string readFile(std::string& dir);
};
#endif
