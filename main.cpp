#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "Shader.h"
#include <tgmath.h>
#include <ft2build.h>
#include "Utilities.h"
#include "Geometry.h"
#include "Object.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H

/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void printTextScreen(int x, int y, std::string str);
glm::mat4 trans;
std::vector<Object> sceneObjects;
FT_Library library;
FT_Face face;
std::string fileVertexShader = "Shaders/vs.glsl";
std::string fileFragmentShader = "Shaders/fs.glsl";
std::string fileFragmentShader2 = "Shaders/fs2.glsl";
glm::mat4 view;
glm::mat4 projection;
const int WIDTH = 800;
const int HEIGHT = 600;
Game Game(WIDTH, HEIGHT);
float color[3] = {0.1,0.7,0.5};
float prueba = 1.0f;
int fps = 0;
float vertices[] =
{
 -0.5f, 0.0f, 0.0f,
  0.5f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};
float timeValue, greenValue;
float lastTimeFPS = 0;
float currentFrame;
int indice;
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
  // FT_Init_FreeType( &library );
  // int error = FT_New_Face(library,"Fonts/Fragmentcore.otf",0,&face);
  // if ( error == FT_Err_Unknown_File_Format )
  //   std::cout<<"Fallo pero no es soportado"<<std::endl;
  // else{
  //   if(error)
  //     std::cout<<"Fallo"<<std::endl;
  // }
  // FT_Set_Char_Size(face,0,16*64,300,300 );
  // unsigned int glyph_index = FT_Get_Char_Index( face, 0x00046 );
  // FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT );
  // FT_Render_Glyph( face->glyph,   /* glyph slot  */
  //                        FT_RENDER_MODE_NORMAL ); /* render mode */
  // FT_GlyphSlot slot = face -> glyph;
  // my_draw_bitmap( &slot->bitmap,
  // 300 + slot->bitmap_left,
  // 200 - slot->bitmap_top );
  glViewport(0, 0, WIDTH, HEIGHT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Game.init();
  float ayuda[] = {13.5,48.0,0.25};
  debug.print((std::string)"TEXTO DEBUG",ayuda,NELEMS(ayuda));
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  Geometry trianguloGeometry(vertices,NELEMS(vertices));
  Shader shader1(fileVertexShader,fileFragmentShader);
  Shader shader2(fileVertexShader,fileFragmentShader2);
  shader1.useShader();
  Object triangulo(trianguloGeometry,shader2);
  Object triangulo2(trianguloGeometry,shader2);
  Object triangulo3(trianguloGeometry,shader2);
  triangulo2.setPosition(glm::vec3(-0.5,-1.0,0.0));
  triangulo3.setPosition(glm::vec3(0.5,-1.0,0.0));
  triangulo.scale(glm::vec3(0.5,0.5,0.5));
  triangulo2.scale(glm::vec3(0.5,0.5,0.5));
  triangulo3.scale(glm::vec3(0.5,0.5,0.5));
  sceneObjects.push_back(triangulo);
  sceneObjects.push_back(triangulo2);
  sceneObjects.push_back(triangulo3);
  view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 10.0f);
  //projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    debug.getFpsCount(currentFrame,&lastTimeFPS);
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
  glClear(GL_COLOR_BUFFER_BIT);
  timeValue = glfwGetTime();
  greenValue= ((sin(timeValue) / 2.0f) + 0.5f);
  for(int i=0; i<sceneObjects.size(); i++)
  {
    sceneObjects[i].getShader().setUniform("view",glm::value_ptr(view));
    sceneObjects[i].getShader().setUniform("projection",glm::value_ptr(projection));
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
  }
}

// void printTextScreen(int x, int y, std::string str){
//   //set the position of the text in the window using the x and y coordinates
//   glRasterPos2f(x,y);
//   //get the length of the string to display
//   int len = (int) (str.size()/sizeof(char));
//   //loop to display character by character
//   for (int i = 0; i < len; i++)
//   {
//   	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
//   }
// }
