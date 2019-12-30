#include "GameEntity.h"
#include "../General/Utilities.h"
GameEntity::GameEntity(Object objeto, glm::vec2 size, glm::vec3 position, unsigned int texture)
  :objeto(objeto), size(size), position(position), texture(texture)
{
  this->setScale(size);
  this->setPosition(position);

}

GameEntity::~GameEntity()
{

}

void GameEntity::setPosition(glm::vec3 position)
{
  glm::vec3 lastPosition = this->objeto.getPosition();
  this->objeto.setPosition(-lastPosition);
  this->objeto.setPosition(position);
  this->position = position;
}

void GameEntity::setScale(glm::vec2 scale)
{
  this->objeto.scale(glm::vec3(scale[0],scale[1],1.0));
  this->size = scale;
}

void GameEntity::setTexture(unsigned int texture)
{
  this->texture = texture;
}


Shader GameEntity::getShader()
{
  return this->objeto.getShader();
}

Object* GameEntity::getObject()
{
  return &this->objeto;
}

glm::vec3 GameEntity::getPosition()
{
  return this->position;
}

glm::vec2 GameEntity::getSize()
{
  return this->size;
}
