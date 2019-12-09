#ifndef DEBUGCLASS_H_
#define DEBUGCLASS_H_
#include <string>
#include <iostream>
class Debug{
public:
  Debug();
  ~Debug();
  template<typename T>void print(std::string str, T* variables, size_t arrayLength)
  {
    if(DEBUG)
    {
      std::cout << str << " " ;
      for(int i = 0; i < arrayLength; i++)
      {
        if(i != 0)
        {
          std::cout << " , " << variables[i] ;
        }
        else
        {
          std::cout << variables[i];
        }
      }

      std::cout << std::endl;
    }
  }
private:
  static const bool DEBUG = false;
};
#endif
