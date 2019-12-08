#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
#include <iostream>
#include <malloc.h>
#include <typeinfo>

Shader::Shader()
{
}
Shader::~Shader()
{

}

unsigned int Shader::createShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
  unsigned int vertex = createShader(vertexShaderSource,GL_VERTEX_SHADER);
  unsigned int fragment = createShader(fragmentShaderSource,GL_FRAGMENT_SHADER);
  unsigned int program = glCreateProgram();
  glAttachShader(program, vertex);
  glAttachShader(program, fragment);
  glLinkProgram(program);
  glUseProgram(program);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  shaderProgram = program;
  aux = 0;
  glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &count);
  aux += count;
  glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
  aux +=count;
  names = new std::string[aux];
  types = new GLenum[aux];
  locations = new int[aux];
  // std::cout << "La cantidad de uniforms y atributes es: " <<aux << std::endl;
  getAttributes();
  getUniforms();
  // for(int i=0; i<aux; i++){
  //   std::cout << "Name " << names[i] << " Type " << types[i] << std::endl;
  // }
  return program;
}
unsigned int Shader::createShader(const std::string& source, GLenum type)
{
  unsigned int shader = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  int result;
  glGetShaderiv(shader,GL_COMPILE_STATUS, &result);
  if(!result)
  {
    int length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(shader, length, &length, message);
    std::cout <<"Failed To Compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader." << std::endl;
    std::cout << message << std::endl;
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

void Shader::useShader()
{
  glUseProgram(shaderProgram);
}

int Shader::getLocation(const std::string& variable)
{
  const char *var = variable.c_str();
  return glGetUniformLocation(shaderProgram, var);
}
//
// template <typename T>void Shader::setUniform(const std::string& variable, T value)
// {
//   bool encontre = false;
//   int indice = 0;
//   T* aux = &value;
//   while(!encontre && indice <= aux )
//   {
//     if(names[indice] == variable)
//     {
//       encontre = true;
//       if(typeid(value).name() == typeid(float*).name())
//         checkUniform(locations[indice],types[indice],value);
//       else
//         checkUniform(locations[indice],types[indice],aux);
//     }
//     else
//     {
//       indice++;
//     }
//   }
//   if(!encontre)
//   {
//     //std::cout << "No se encontro el uniform deseado" << std::endl;
//   }
// }

void Shader::getAttributes()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &count);
  // printf("Active Attributes: %d\n", count);

  for (int i = 0; i < count; i++)
  {
      glGetActiveAttrib(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      indexSaved++;
      //printf("Attribute #%d Type: %u Name: %s\n", i, type, name);
  }
}

void Shader::getUniforms()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
  // printf("Active Uniforms: %d\n", count);

  for (int i = 0; i < count; i++)
  {
      glGetActiveUniform(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      locations[indexSaved] = glGetUniformLocation(shaderProgram,name);
      indexSaved++;
      //printf("Uniform #%d Type: %u Name: %s\n", i, type, name);
  }
}

// template<typename T>void Shader::checkUniform(int location, GLenum type, T value)
// {
//   switch(type)
//   {
//     case(GL_FLOAT):       glUniform1f(location,(*(float)value));
//                           break;
//     case(GL_INT):         glUniform1i(location,(*(int)value));
//                           break;
//     case(GL_BOOL):        glUniform1i(location,(*(int)value));
//                           break;
//     case(GL_FLOAT_VEC2):  glUniform2f(location,(*(float*)value)[0],(*(float*)value)[1]);
//                           break;
//     case(GL_FLOAT_VEC3):  glUniform3f(location,(*(float*)value)[0],(*(float*)value)[1],(*(float*)value)[2]);
//                           break;
//     case(GL_FLOAT_VEC4):  glUniform4f(location,(*(float*)value)[0],(*(float*)value)[1],(*(float*)value)[2],(*(float*)value)[3]);
//                           break;
//   }
// }
// template<typename T> void Shader::checkUniform(int location, GLenum type, T value)
// {
//
//   // if(type == GL_FLOAT)
//   //   glUniform1f(location,1,value);
//   if(type == GL_INT)
//     glUniform1i(location,1,value);
//   // switch(type)
//   // {
//   //   case(GL_FLOAT):       glUniform1fv(location,1,value);
//   //                         break;
//   //   case(GL_INT):         glUniform1iv(location,1,value);
//   //                         break;
//   //   // case(GL_BOOL):        glUniform1iv(location,1,value);
//   //   //                       break;
//   //   case(GL_FLOAT_VEC2):  glUniform2fv(location,2,value);
//   //                         break;
//   //   case(GL_FLOAT_VEC3):  glUniform3fv(location,3,value);
//   //                         break;
//   //   case(GL_FLOAT_VEC4):  glUniform4fv(location,4,value);
//   //                         break;
//   // }
// }
//
// template<typename T> void Shader::setUniform(const std::string& variable, T value)
// {
//   bool encontre = false;
//   int indice = 0;
//   while(!encontre && indice <= aux )
//   {
//     if(names[indice] == variable)
//     {
//       encontre = true;
//       checkUniform(locations[indice],types[indice],value);
//     }
//     else
//     {
//       indice++;
//     }
//   }
//   if(!encontre)
//   {
//     std::cout << "No se encontro el uniform deseado" << std::endl;
//   }
// }
