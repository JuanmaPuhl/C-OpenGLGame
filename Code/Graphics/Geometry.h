#ifndef GEOMETRY_H_
#define GEOMETRY_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Geometry
{
public:
  Geometry(float* data, size_t dataSize, float* texCoords, size_t sizeCoords);
  ~Geometry();
  unsigned int getVAO();
  unsigned int getVBO();
  float* getData();
  size_t getDataSize();

private:
  unsigned int VAO;
  unsigned int VBO;
  float* data;
  size_t dataSize;
  float* texCoords;
  size_t sizeCoords;
};
#endif
