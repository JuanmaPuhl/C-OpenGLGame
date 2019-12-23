#include "GameEntity.h"
#include "Utilities.h"
GameEntity::GameEntity(Object* objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color)
  :objeto(objeto), size(size), position(position), color(color)
{
  this->setPosition(position);
}

GameEntity::~GameEntity()
{

}

void GameEntity::setPosition(glm::vec3 position)
{
  glm::vec3 lastPosition = this->objeto->getPosition();
  this->objeto->setPosition(-lastPosition);
  this->objeto->setPosition(position);
  this->position = position;
}

void GameEntity::setColor(glm::vec3 color)
{
  this->color = color;
}


Shader GameEntity::getShader()
{
  return this->objeto->getShader();
}

Object* GameEntity::getObject()
{
  return this->objeto;
}
