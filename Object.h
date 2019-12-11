#ifndef OBJECT_H_
#define OBJECT_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Geometry.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
public:
  Object(Geometry geometry,Shader shader);
  ~Object();
  void drawObject();
  unsigned int getVAO();
  void setPosition(glm::vec3 position);
  Shader getShader();
  glm::mat4 getModelMatrix();
private:
  unsigned int VBO;
  unsigned int VAO;
  Shader shader;
  float* data;
  size_t dataSize;
  glm::mat4 modelMatrix;
};

#endif
