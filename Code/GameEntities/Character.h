#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "GameEntity.h"
class Character : public GameEntity
{
public:
  Character(Object objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color);
  ~Character();
  void moveCharacter();
  void move(glm::vec2 direction);
  void render()
  {
    static_cast<Character*>(this)->moveCharacter();
    Shader shader = this->objeto.getShader();
    shader.useShader();
    shader.setUniform("color",glm::value_ptr(this->color));
    shader.setUniform("transform",glm::value_ptr(this->objeto.getModelMatrix()));
    this->objeto.drawObject();
  }

private:
  float velocidad = 5.0f;
  int directionX = 0;
  int directionY = 0;
};
#endif