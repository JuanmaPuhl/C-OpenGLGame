#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
class FileManager
{
public:
  FileManager();
  ~FileManager();
  std::string readFile(std::string& dir);
  std::vector<std::string> parseFile(std::string& source);
};
#endif
