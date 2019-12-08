#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "Shader.h"
# include <fstream>
# include <sstream>
#include <tgmath.h>

std::string fileVertexShader = "Shaders/vs.glsl";
std::string fileFragmentShader = "Shaders/fs.glsl";
std::string fileFragmentShader2 = "Shaders/fs2.glsl";
const int WIDTH = 800;
const int HEIGHT = 600;
Shader shader1;
Shader shader2;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
std::string readFile(std::string& dir);
Game Game(WIDTH, HEIGHT);

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
  //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Game.init();
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  float vertices[] = {
   -0.5f, 0.0f, 0.0f,
    0.5f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  };
  float vertices2[] = {
   -0.5f, 0.0f, 0.0f,
    0.0f,-1.0f, 0.0f,
    0.5f, 0.0f, 0.0f
  };
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  unsigned int VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  const std::string vertexShaderSource = readFile(fileVertexShader);
  const std::string fragmentShaderSource = readFile(fileFragmentShader);
  const std::string fragmentShaderSource2 = readFile(fileFragmentShader2);
  shader1.createShaderProgram(vertexShaderSource,fragmentShaderSource);
  shader2.createShaderProgram(vertexShaderSource,fragmentShaderSource2);
  float timeValue = glfwGetTime();
  float greenValue = (float)(sin(timeValue) / 2.0f) + 0.5f;
  shader1.useShader();
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  unsigned int VAO2;
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  float color[3] = {1.0f,0.0f,0.0f};
  int prueba = 2;
  while (!glfwWindowShouldClose(window))
  {
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    Game.update(deltaTime);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    timeValue = glfwGetTime();
    greenValue= ((sin(timeValue) / 2.0f) + 0.5f);
    shader2.setUniform("fade",&greenValue);
    shader1.setUniform("color",color);
    shader1.setUniform("prueba",&prueba);
    shader1.useShader();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(*vertices) / 3);
    shader2.useShader();
    glBindVertexArray(VAO2);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices2)/sizeof(*vertices2) / 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
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
  }
}

std::string readFile(std::string& dir)
{
  std::ifstream file{dir};
  std::string const fileContent = static_cast<std::ostringstream&>
      (std::ostringstream{} << file.rdbuf()).str();
  // std::cout << fileContent << std::endl;
  return fileContent;
}
