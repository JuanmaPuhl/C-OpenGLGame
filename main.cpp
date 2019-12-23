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
#include "GameEntity.h"
#include "Character.h"
#define WIDTH 1280
#define HEIGHT 720

/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
/*Variables globales*/
std::vector<GameEntity*> sceneObjects;
Shader *shaderTexto;
Shader *shaderQuad;
std::string fileShaderText = "Shaders/shaderText.shader";
std::string fileShaderQuad = "Shaders/shaderQuad.shader";
Game Game(WIDTH, HEIGHT);
float verticesQuad[] =
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
  /*=====================INICIA CREACION DE VENTANA==========================*/
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
  /*====================TERMINA CREACION DE VENTANA==========================*/
  /*========================CREACION OBJETOS=================================*/
  Geometry quadGeometry(verticesQuad,NELEMS(verticesQuad));
  shaderTexto = new Shader(fileShaderText);
  shaderQuad = new Shader(fileShaderQuad);
  Object player(quadGeometry,*shaderQuad);
  Object bloque(quadGeometry,*shaderQuad);
  player.scale(glm::vec3(32.0,32.0,1.0));
  bloque.scale(glm::vec3(32.0,32.0,1.0));
  GameEntity* playerEntity = new Character(&player,glm::vec2(32.0),glm::vec3(0.0),glm::vec3(0.8,0.0,0.80));
  GameEntity* floorEntity = new Character(&bloque,glm::vec2(32.0),glm::vec3(128.0,0.0,0.0),glm::vec3(0.0,0.8,0.0));
  sceneObjects.push_back(playerEntity);
  sceneObjects.push_back(floorEntity);
  fontManager = new FontManager();
  /*======================FIN CREACION OBJETOS===============================*/
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Game.init();
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
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
  shaderTexto->useShader();
  shaderTexto->setUniform("projection",glm::value_ptr(camera.getHUDProjectionMatrix()));
  fontManager->RenderText(*shaderTexto, "FPS: ", 3.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  fontManager->RenderText(*shaderTexto, std::to_string(debug.getFpsCount(currentFrame,&lastTimeFPS)), 53.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  for(GameEntity* entidad : sceneObjects)
  {
    entidad->getShader().useShader();
    entidad->getShader().setUniform("view",glm::value_ptr(camera.getViewMatrix()));
    entidad->getShader().setUniform("projection",glm::value_ptr(camera.getProjectionMatrix()));
    entidad->render();
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
    glm::vec2 direction = glm::vec2(0.0);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      direction[0] = -1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      direction[0] = 1;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
      direction[0] = 0;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      direction[1] = 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      direction[1] = -1;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
      direction[1] = 0;
    static_cast<Character*>(sceneObjects[0])->move(direction);

    if(glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
      camera.zoomCamera(1);
    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
      camera.zoomCamera(-1);
    if(glfwGetKey(window, GLFW_KEY_U) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_J) == GLFW_RELEASE)
      camera.zoomCamera(0.0);


    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
      camera.moveCamera(1);
    if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
      camera.moveCamera(-1);
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
      camera.moveCamera(0);

  }
}
