#ifndef ORTOGRAPHIC_CAMERA_H_
#define ORTOGRAPHIC_CAMERA_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class OrtographicCamera
{
public:
  OrtographicCamera();
  ~OrtographicCamera();
  void refreshViewMatrix();
  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();
  void moveCamera(int dir);
private:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 cameraTarget;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 cameraRight;
  glm::vec3 cameraUp;
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  float velocity = 0.05f;
};
#endif
