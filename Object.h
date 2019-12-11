#ifndef OBJECT_H_
#define OBJECT_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Shader.h"
#include "Geometry.h"
class Object
{
public:
  Object(Geometry geometry,Shader shader);
  ~Object();
  void drawObject();
  unsigned int getVAO();
private:
  unsigned int VBO;
  unsigned int VAO;
  Shader shader;
  float* data;
  size_t dataSize;
};

#endif
