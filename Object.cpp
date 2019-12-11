#include "Object.h"

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
  this->modelMatrix = glm::mat4();
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

void Object::setPosition(glm::vec3 position)
{
  glm::mat4 translationMatrix = glm::mat4();
  translationMatrix = glm::translate(translationMatrix,position);
  this->modelMatrix = translationMatrix * (this->modelMatrix);
}

Shader Object::getShader()
{
  return this->shader;
}

glm::mat4 Object::getModelMatrix()
{
  return this->modelMatrix;
}
