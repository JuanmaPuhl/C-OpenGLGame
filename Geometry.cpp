#include "Geometry.h"

Geometry::Geometry(float* data, size_t dataSize, float* texCoords, size_t sizeCoords)
{
  int aux = 0;
  int* paux = &aux;
  this -> data = data;
  this -> dataSize = dataSize;
  this -> texCoords = texCoords;
  this -> sizeCoords = sizeCoords;
  unsigned int vboAux;
  glGenBuffers(1, &(this -> VBO));
  glGenVertexArrays(1, &(this->VAO));
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->dataSize * sizeof(this->data), this->data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glGenBuffers(1,&vboAux);
  glBindBuffer(GL_ARRAY_BUFFER, vboAux);
  glBufferData(GL_ARRAY_BUFFER, this->sizeCoords * sizeof(this->texCoords), this->texCoords, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Geometry::~Geometry()
{
}

unsigned int Geometry::getVAO()
{
  return this->VAO;
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
