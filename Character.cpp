#include "Character.h"

Character::Character(Object* objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color)
  :GameEntity(objeto, size, position, color)
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

void Character::moveCharacter()
{
  glm::vec3 newPosition = this->position + glm::vec3(this->directionX * this->velocidad,this->directionY * this->velocidad,0.0);
  this->setPosition(newPosition);

}
void GameEntity::render()
{
  static_cast<Character*>(this)->moveCharacter();
  Shader shader = this->objeto->getShader();
  shader.useShader();
  shader.setUniform("color",glm::value_ptr(this->color));
  shader.setUniform("transform",glm::value_ptr(this->objeto->getModelMatrix()));
  this->objeto->drawObject();
}
