#ifndef ORTOGRAPHIC_CAMERA_H_
#define ORTOGRAPHIC_CAMERA_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../GameEntities/GameEntity.h"

class OrtographicCamera
{
public:
  OrtographicCamera(int width, int height);
  ~OrtographicCamera();
  void updateCamera(float deltaTime);
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
  glm::mat4 getHUDProjectionMatrix();
  void moveCamera(int dir);
  void zoomCamera(int zoom);
  void followEntity(GameEntity* entity);
private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 cameraTarget;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 cameraRight;
  glm::vec3 cameraUp;
  glm::mat4 projectionMatrix;
  glm::mat4 HUDProjectionMatrix;
  glm::mat4 viewMatrix;
  float velocity = 50.0f;
  float zoom = 1.0f;
  int height;
  int width;
  int zoomOrder = 0;
  float zoomVelocity = 1.0f;
  int movementDirection = 0;
};
#endif
