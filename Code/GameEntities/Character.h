#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "GameEntity.h"
class Character : public GameEntity
{
public:
  Character(Object objeto, glm::vec2 size, glm::vec3 position, unsigned int texture);
  ~Character();
  void moveCharacter(float deltaTime);
  void move(glm::vec2 direction);
  void render(float deltaTime)
  {
    static_cast<Character*>(this)->moveCharacter(deltaTime);
    Shader shader = this->objeto.getShader();
    shader.useShader();
    //shader.setUniform("color",glm::value_ptr(this->color));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    shader.setUniform("transform",glm::value_ptr(this->objeto.getModelMatrix()));
    this->objeto.drawObject();
  }

private:
  float velocidad = 256.0f;
  int directionX = 0;
  int directionY = 0;
};
#endif
