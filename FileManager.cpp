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

std::vector<std::string> FileManager::parseFile(std::string& source)
{
  std::ifstream file{source};
  std::string lineContent;
  enum class ShaderType
  {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };
  ShaderType type = ShaderType::NONE;
  std::stringstream ss[2];
  while(getline(file,lineContent))
  {
    if(lineContent.find("<Shader>") != std::string::npos)
    {
      if(lineContent.find("Vertex") != std::string::npos)
      {
        type = ShaderType::VERTEX;
      }
      else if(lineContent.find("Fragment") != std::string::npos)
      {
        type = ShaderType::FRAGMENT;
      }
    }
    else
    {
      if((int)type != -1)
        ss[(int)type] << lineContent << '\n';
    }

  }
  std::vector<std::string> vectorSource;
  vectorSource.push_back(ss[0].str());
  vectorSource.push_back(ss[1].str());
  return vectorSource;

}
