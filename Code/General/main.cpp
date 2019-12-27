#include <GL/glew.h>//
#include <GLFW/glfw3.h>//
#include "Game.h"
#define WIDTH 1280
#define HEIGHT 720

/*Declaraciplayers previas de funciplayers implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Game Game(WIDTH, HEIGHT);
float currentFrame = 0.0f;
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
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.init();
  Game.State = GAME_ACTIVE;
  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    Game.update(currentFrame,deltaTime);
    Game.render();
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

// float distance(float v1, float v2)
// {
//   //std::cout<<"V1 es: "<<v1<<" V2 es: "<<v2<<std::endl;
//   return abs(abs(v1)-abs(v2));
// }
//
// bool checkCollisions()
// {
//   glm::vec3 positionPlayer = player->getPosition();
//   glm::vec2 sizePlayer = player->getSize();
//   for(GameEntity* entidad : levelObjects)
//   {
//     glm::vec3 positionObject = entidad->getPosition();
//     glm::vec2 sizeObject = entidad->getSize();
//     // Collision x-axis?
//     bool collisionX = positionPlayer.x + sizePlayer.x >= positionObject.x - sizeObject.x ||
//                       positionPlayer.x - sizePlayer.x <= positionObject.x + sizeObject.x;
//
//     // Collision y-axis?
//     bool collisionY = positionPlayer.y + sizePlayer.y >= positionObject.y &&
//         positionObject.y + sizeObject.y >= positionPlayer.y;
//     // Collision only if on both axes
//     if(collisionX && collisionY)
//     {
//       fontManager->RenderText(*shaderTexto, "X", positionObject.x + float(WIDTH/2) - 7.5f, -positionObject.y + float(HEIGHT/2) - 80.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
//       //player->setPosition(positionObject - glm::vec3(float(sizeObject.x*2.0f),0.0,0.0));
//     }
//
//   }
// }
