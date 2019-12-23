#include "Object.h"
#include "Utilities.h"
Object::Object(Geometry geometry,const Shader& shader):
  shader(shader)
{
  this->VBO = geometry.getVBO();
  this->data = geometry.getData();
  this->dataSize = geometry.getDataSize();
  glGenVertexArrays(1, &(this->VAO));
  glBindVertexArray(this->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  glBufferData(GL_ARRAY_BUFFER, this->dataSize * sizeof(this->data), this->data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  this->modelMatrix = glm::mat4(1.0f);
  this->position = glm::vec3(0.0f,0.0f,0.0f);
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
  glm::mat4 translationMatrix = glm::mat4(1.0f);
  translationMatrix = glm::translate(translationMatrix,position);
  this->modelMatrix = translationMatrix * (this->modelMatrix);
  this->position = position;
}

void Object::rotate(float angle, glm::vec3 axis,int mode)
{
  glm::mat4 trans = glm::mat4(1.0f);
  if(!mode)
  {
    trans = glm::rotate(trans, glm::radians(angle), axis);
    this->modelMatrix = trans * this->modelMatrix;
  }
  else
  {
    glm::vec3 lastPosition = this->position;
    this->setPosition(-1.0f * lastPosition);
    trans = glm::rotate(trans,glm::radians(angle),axis);
    this->modelMatrix = trans * this->modelMatrix;
    this->setPosition(lastPosition);
  }
}

void Object::scale(glm::vec3 scale)
{
  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::scale(trans,scale);
  this->modelMatrix = trans * this->modelMatrix;
}

Shader Object::getShader()
{
  return this->shader;
}

glm::mat4 Object::getModelMatrix()
{
  return this->modelMatrix;
}

glm::vec3 Object::getPosition()
{
  return this->position;
}

glm::vec2 Object::getRotation()
{

  return glm::vec2(0.0);
}

glm::vec3 Object::getScale()
{
  return glm::vec3(0.0);
}
