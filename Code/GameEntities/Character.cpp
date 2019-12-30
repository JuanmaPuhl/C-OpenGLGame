#include "Character.h"

Character::Character(Object objeto, glm::vec2 size, glm::vec3 position, unsigned int texture)
  :GameEntity(objeto, size, position, texture)
{

}

Character::~Character()
{

}

void Character::move(glm::vec2 direction)
{
  this->directionX = direction[0];
  this->directionY = direction[1];
}

void Character::moveCharacter(float deltaTime)
{
  glm::vec3 newPosition = this->position + glm::vec3(
      this->directionX * this->velocidad * deltaTime,
      this->directionY * this->velocidad * deltaTime,
      0.0);
  this->setPosition(newPosition);
}
