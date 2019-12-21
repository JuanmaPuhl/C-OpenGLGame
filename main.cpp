#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "Shader.h"
#include <tgmath.h>
#include "Utilities.h"
#include "Geometry.h"
#include "Object.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "OrtographicCamera.h"

/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
std::vector<Object> sceneObjects;
std::vector<Shader> shaders;
std::string fileVertexShader = "Shaders/vs.glsl";
std::string fileVertexShader2 = "Shaders/vs2.glsl";
std::string fileFragmentShader = "Shaders/fs.glsl";
std::string fileFragmentShader2 = "Shaders/fs2.glsl";
const int WIDTH = 1280;
const int HEIGHT = 720;
Game Game(WIDTH, HEIGHT);
float color[3] = {0.1,0.7,0.5};
float prueba = 1.0f;
float vertices[] =
{
  1.0f, 1.0f, 0.0f,
 -1.0f, 1.0f, 0.0f,
  1.0f,-1.0f, 0.0f,
 -1.0f, 1.0f, 0.0f,
 -1.0f,-1.0f, 0.0f,
  1.0f,-1.0f, 0.0f
};
float timeValue, greenValue;
float lastTimeFPS = 0;
float currentFrame;
int indice;
FontManager* fontManager;
OrtographicCamera camera(WIDTH,HEIGHT);

int main(void)
{
  GLFWwindow* window;
  if (!glfwInit())
  {
    return -1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  window = glfwCreateWindow(WIDTH, HEIGHT, "Game", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();
  glGetError();
  glViewport(0, 0, WIDTH, HEIGHT);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Game.init();
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  Geometry quadGeometry(vertices,NELEMS(vertices));
  Shader shader1(fileVertexShader,fileFragmentShader);
  Shader shader2(fileVertexShader2,fileFragmentShader2);
  shaders.push_back(shader1);
  shaders.push_back(shader2);
  shader1.useShader();
  Object player(quadGeometry,shader2);
  player.scale(glm::vec3(100.0,100.5,1.0));
  player.setPosition(glm::vec3(float(WIDTH / 2),float(HEIGHT/2),0.0f));
  sceneObjects.push_back(player);

  fontManager = new FontManager();
  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    // debug.getFpsCount(currentFrame,&lastTimeFPS);
    Game.update(deltaTime);

    render();
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

void render()
{
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  timeValue = glfwGetTime();
  greenValue= ((sin(timeValue) / 2.0f) + 0.5f);
  camera.refreshViewMatrix();
  for(Shader shader : shaders)
  {
    shader.useShader();
    shader.setUniform("projection",glm::value_ptr(camera.getProjectionMatrix()));
  }
  fontManager->RenderText(shaders[0], "FPS: ", 3.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  fontManager->RenderText(shaders[0], std::to_string(debug.getFpsCount(currentFrame,&lastTimeFPS)), 53.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));

  for(int i=0; i<sceneObjects.size(); i++)
  {
    sceneObjects[i].getShader().useShader();
    sceneObjects[i].getShader().setUniform("view",glm::value_ptr(camera.getViewMatrix()));
    sceneObjects[i].getShader().setUniform("projection",glm::value_ptr(camera.getProjectionMatrix()));
    sceneObjects[i].getShader().setUniform("transform",glm::value_ptr(sceneObjects[i].getModelMatrix()));
    sceneObjects[i].getShader().setUniform("fade",&greenValue);
    sceneObjects[i].getShader().setUniform("color",color);
    sceneObjects[i].getShader().setUniform("prueba",&prueba);
    sceneObjects[i].drawObject();
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key >= 0 && key < 1024)
  {
    if (action == GLFW_PRESS)
    Game.Keys[key] = GL_TRUE;
    else if (action == GLFW_RELEASE)
    Game.Keys[key] = GL_FALSE;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.moveCamera(-1);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.moveCamera(1);
  }
}
