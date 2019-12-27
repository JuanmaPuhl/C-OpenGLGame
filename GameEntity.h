#ifndef GAME_ENTITY_H_
#define GAME_ENTITY_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
class GameEntity
{
public:
  GameEntity(Object objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color);
  ~GameEntity();
  void setPosition(glm::vec3 position);
  void setColor(glm::vec3 color);
  virtual void render() = 0;
  Shader getShader();
  Object* getObject();
  void setScale(glm::vec2 scale);
  glm::vec3 getPosition();
  glm::vec2 getSize();
  glm::vec3 position = glm::vec3(0.0);
  glm::vec2 size = glm::vec2(1.0);
  glm::vec3 color = glm::vec3(1.0); //Como color por defecto, es blanco
  Object objeto;
};
#endif
