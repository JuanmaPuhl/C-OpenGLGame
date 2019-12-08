#ifndef OBJECT_H_
#define OBJECT_H_
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>
#include <stdio.h>
#include "Shader.h"
class Object
{
public:
  Object();
  ~Object();
  void setVertices(float* vertices);
  void createVBO();
  void createVAO();
  void setShader(Shader shader);
  void drawObject();

private:
  float* vertices;
  unsigned int VBO;
  unsigned int VAO;
  Shader shader;
};

#endif
