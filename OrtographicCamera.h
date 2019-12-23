#ifndef ORTOGRAPHIC_CAMERA_H_
#define ORTOGRAPHIC_CAMERA_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class OrtographicCamera
{
public:
  OrtographicCamera(int width, int height);
  ~OrtographicCamera();
  void refreshViewMatrix();
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
  glm::mat4 getHUDProjectionMatrix();
  void moveCamera(int dir);
  void zoomCamera(int zoom);
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
  float velocity = 10.0f;
  float zoom = 1.0f;
  int height;
  int width;
  int zoomOrder = 0;
  float zoomVelocity = 0.01f;
};
#endif
