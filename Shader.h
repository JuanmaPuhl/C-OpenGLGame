#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
class Shader
{
public:
  Shader();
  ~Shader();
  unsigned int createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
  unsigned int createShader(const std::string& source, GLenum type);
  void useShader();
  int getLocation(const std::string& variable);
  void setUniform(const std::string& variable, void* value);

private:
  void getAttributes();
  void getUniforms();
  void checkUniform(int location, GLenum type, void* value);
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
