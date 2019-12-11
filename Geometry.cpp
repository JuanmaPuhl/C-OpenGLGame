#include "Geometry.h"

Geometry::Geometry(float* data, size_t size)
{
  int aux = 0;
  int* paux = &aux;
  this -> data = data;
  this -> dataSize = size;
  int dataToWrite = this->dataSize * sizeof(this->data);
  unsigned int vboAux;
  glGenBuffers(1, &(this -> VBO));
  glBindBuffer(GL_ARRAY_BUFFER, this -> VBO);
  glBufferData(GL_ARRAY_BUFFER, this->dataSize * sizeof(this->data), this->data, GL_STATIC_DRAW);
}

Geometry::~Geometry()
{
}

unsigned int Geometry::getVBO()
{
  return this->VBO;
}

float* Geometry::getData()
{
  return this->data;
}

size_t Geometry::getDataSize()
{
  return this->dataSize;
}
