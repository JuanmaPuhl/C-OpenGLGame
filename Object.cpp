#include "Object.h"

Debug debugObject;
Object::Object(Geometry geometry, Shader shader)
{
  this->VBO = geometry.getVBO();
  this->data = geometry.getData();
  this->dataSize = geometry.getDataSize();
  this->shader = shader;
  glGenVertexArrays(1, &(this->VAO));
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->dataSize * sizeof(this->data), this->data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}
Object::~Object()
{
}

void Object::drawObject()
{
  this->shader.useShader();
  glBindVertexArray(this->VAO);
  glDrawArrays(GL_TRIANGLES, 0, this->dataSize / 3);
}

unsigned int Object::getVAO()
{
  return this->VAO;
}
