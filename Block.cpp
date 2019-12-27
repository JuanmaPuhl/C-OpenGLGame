#include "Block.h"

Block::Block(Object objeto, glm::vec2 size, glm::vec3 position, glm::vec3 color, bool solid)
  :GameEntity(objeto, size, position, color)
{
  this->solid = solid;
}

Block::~Block()
{

}

bool Block::isSolid()
{
  return this->solid;
}
