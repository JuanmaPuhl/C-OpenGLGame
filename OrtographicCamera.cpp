#include "OrtographicCamera.h"

OrtographicCamera::OrtographicCamera(int width, int height)
{
  this->up = glm::vec3(0.0f,1.0f,0.0f);
  this->direction = glm::vec3(0.0f,0.0f,0.0f);
  this->projectionMatrix = glm::ortho(0.0f, float(width), float(height), 0.0f, -1.0f, 10.0f);
  this->position = glm::vec3(0.0f, 0.0f, 3.0f);
  this->front = glm::vec3(0.0f, 0.0f, -1.0f);
  this->viewMatrix = glm::mat4(1.0f);
  this->cameraTarget = glm::normalize(position - direction);
  this->cameraRight = glm::normalize(glm::cross(up, cameraTarget));
  this->cameraUp = glm::cross(cameraTarget, cameraRight);
}
OrtographicCamera::~OrtographicCamera()
{

}

void OrtographicCamera::refreshViewMatrix()
{
  this->viewMatrix = glm::lookAt(position,position + front, up);
}

glm::mat4 OrtographicCamera::getViewMatrix()
{
  return this->viewMatrix;
}
glm::mat4 OrtographicCamera::getProjectionMatrix()
{
  return this->projectionMatrix;
}

void OrtographicCamera::moveCamera(int dir)
{
  this->position += (float)dir * glm::normalize(glm::cross(this->front, this->cameraUp)) * this->velocity;
}
