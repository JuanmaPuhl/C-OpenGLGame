#ifndef DEBUGCLASS_H_
#define DEBUGCLASS_H_
#include <string>
#include <iostream>

class Debug{
public:
  Debug();
  ~Debug();
  /*Funcion para imprimir por pantalla*/
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
  int getFpsCount(float current, float* lastTime);

private:
  static const bool DEBUG = true;
  int fps = 0;
  int fpsConstantes = 0;
};
#endif
