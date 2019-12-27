#ifndef SOLID_BLOCK_H_
#define SOLID_BLOCK_H_
#include "GameEntity.h"
class Block : public GameEntity
{
public:
  Block(Object objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color, bool solid);
  ~Block();
  bool isSolid();
  void render(float deltaTime)
  {
    Shader shader = this->objeto.getShader();
    shader.useShader();
    shader.setUniform("color",glm::value_ptr(this->color));
    shader.setUniform("transform",glm::value_ptr(this->objeto.getModelMatrix()));
    this->objeto.drawObject();
  }
private:
  bool solid = false;
};
#endif
