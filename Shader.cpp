#include "Shader.h"
#include <malloc.h>


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
  getAttributes();
  getUniforms();
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

void Shader::getAttributes()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_ATTRIBUTES, &count);
  for (int i = 0; i < count; i++)
  {
      glGetActiveAttrib(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      indexSaved++;
  }
}

void Shader::getUniforms()
{
  glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &count);
  for (int i = 0; i < count; i++)
  {
      glGetActiveUniform(shaderProgram, (GLuint)i, bufSize, &length, &size, &type, name);
      names[indexSaved] = name;
      types[indexSaved] = type;
      locations[indexSaved] = glGetUniformLocation(shaderProgram,name);
      indexSaved++;
  }
}

unsigned int Shader::getShaderProgram()
{
  return this->shaderProgram;
}
