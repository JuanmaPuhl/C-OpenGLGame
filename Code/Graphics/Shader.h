#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <typeinfo>
class Shader
{
public:
  Shader(std::string& source);
  ~Shader();
  void useShader();
  unsigned int getShaderProgram();
  int getLocation(const std::string& variable);
  /*Tiene que estar aca por razones de fuerza mayor*/
  template <typename T>void setUniform(const std::string& variable, T value)
  {
    bool encontre = false;
    int indice = 0;

    while(!encontre && indice <= aux )
    {
      if(names[indice] == variable)
      {
        encontre = true;
        checkUniform(locations[indice],types[indice],value);
      }
      else
      {
        indice++;
      }
    }
  }

private:
  unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
  unsigned int createShader(const std::string& source, GLenum type);
  void getAttributes();
  void getUniforms();
  /*Tiene que estar aca por razones de fuerza mayor*/
  template<typename T>void checkUniform(int location, GLenum type, T value)
  {
    switch(type)
    {
      case(GL_FLOAT):       glUniform1f(location,(*value));
                            break;
      case(GL_INT):         glUniform1i(location,(*value));
                            break;
      case(GL_BOOL):        glUniform1i(location,(*value));
                            break;
      case(GL_FLOAT_VEC2):  glUniform2fv(location,1,value);
                            break;
      case(GL_FLOAT_VEC3):  glUniform3fv(location,1,value);
                            break;
      case(GL_FLOAT_VEC4):  glUniform4fv(location,1,value);
                            break;
      case(GL_FLOAT_MAT4):  glUniformMatrix4fv(location, 1, GL_FALSE, value);
                            break;
    }
  }
  GLint count;
  GLint size; // size of the variable
  GLenum type; // type of the variable (float, vec3 or mat4, etc)
  static const int bufSize = 16; // maximum name length
  char name[bufSize]; // variable name in GLSL
  int length; // name length
  unsigned int shaderProgram;
  std::string message;
  int indexSaved = 0;
  std::string* names;
  GLenum* types;
  int* locations;
  int aux;
};
#endif
