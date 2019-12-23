#include "OrtographicCamera.h"

OrtographicCamera::OrtographicCamera(int width, int height)
{
  this->width = width;
  this->height = height;
  this->up = glm::vec3(0.0f,1.0f,0.0f);
  this->direction = glm::vec3(0.0f,0.0f,0.0f);
  this->projectionMatrix = glm::ortho(-float(width/2), float(width/2), -float(height/2),float(height/2), -1.0f, 10.0f);
  this->HUDProjectionMatrix = glm::ortho(0.0f, float(width), float(height),0.0f, -1.0f, 10.0f);
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
  if(this->zoomOrder!=0)
  {
    this->zoom -= this->zoomOrder*this->zoomVelocity;
    this->projectionMatrix = glm::ortho(-float(this->width/2)*this->zoom, float(this->width/2)*this->zoom, -float(this->height/2)*this->zoom, float(this->height/2)*this->zoom, -1.0f, 10.0f);
  }
}

void OrtographicCamera::zoomCamera(int zoomOrder)
{
  this->zoomOrder = zoomOrder;
}

glm::mat4 OrtographicCamera::getViewMatrix()
{
  return this->viewMatrix;
}
glm::mat4 OrtographicCamera::getProjectionMatrix()
{
  return this->projectionMatrix;
}

glm::mat4 OrtographicCamera::getHUDProjectionMatrix()
{
  return this->HUDProjectionMatrix;
}

void OrtographicCamera::moveCamera(int dir)
{
  this->position += (float)dir * glm::normalize(glm::cross(this->front, this->cameraUp)) * this->velocity;
}
