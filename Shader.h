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
  Shader();
  ~Shader();
  unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
  unsigned int createShader(const std::string& source, GLenum type);
  void useShader();
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
    if(!encontre)
    {
      //std::cout << "No se encontro el uniform deseado" << std::endl;
    }
  }

private:
  void getAttributes();
  void getUniforms();
  /*Tiene que estar aca por razones de fuerza mayor*/
  template<typename T>void checkUniform(int location, GLenum type, T value)
  {
    float aux;
    float* auxP;
    switch(type)
    {
      case(GL_FLOAT):       glUniform1f(location,(*value));
                            break;
      case(GL_INT):         glUniform1i(location,(*value));
                            break;
      case(GL_BOOL):        glUniform1i(location,(*value));
                            break;
      case(GL_FLOAT_VEC2):  aux= *value;
                            auxP = &aux;
                            glUniform2f(location,(auxP[0]),(auxP[1]));
                            break;
      case(GL_FLOAT_VEC3):  aux= *value;
                            auxP = &aux;
                            glUniform3f(location,(auxP[0]),(auxP[1]),(auxP[2]));
                            break;
      case(GL_FLOAT_VEC4):  aux= *value;
                            auxP = &aux;
                            glUniform4f(location,(auxP[0]),(auxP[1]),(auxP[2]),(auxP[3]));
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
