#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <tgmath.h>
#include <ft2build.h>
#include "Utilities.h"
#include "Geometry.h"
#include "Object.h"
#include <vector>
#include FT_FREETYPE_H
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void getFpsCount(float current,float* lastTime);
std::string readFile(std::string& dir);
void printTextScreen(int x, int y, std::string str);

std::vector<Object> sceneObjects;
//Debug debug;
FT_Library library;
FT_Face face;
std::string fileVertexShader = "Shaders/vs.glsl";
std::string fileFragmentShader = "Shaders/fs.glsl";
std::string fileFragmentShader2 = "Shaders/fs2.glsl";
Shader shader1,shader2;
const int WIDTH = 800;
const int HEIGHT = 600;
Game Game(WIDTH, HEIGHT);
unsigned int VAO,VAO2,VAO3;
float color[3] = {0.1,0.7,0.5};
float prueba = 1.0f;
int fps = 0;
float vertices[] =
{
 -0.5f, 0.0f, 0.0f,
  0.5f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};
float vertices2[] =
{
 -0.5f, 0.0f, 0.0f,
 -1.0f,-1.0f, 0.0f,
  0.0f,-1.0f, 0.0f
};
float vertices3[] =
{
  0.5f, 0.0f, 0.0f,
  0.0f,-1.0f, 0.0f,
  1.0f,-1.0f, 0.0f
};

float timeValue, greenValue;
float lastTimeFPS = 0;
float currentFrame;
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
  Geometry trianguloGeometry2(vertices2,NELEMS(vertices2));
  Geometry trianguloGeometry3(vertices3,NELEMS(vertices3));
  const std::string vertexShaderSource = readFile(fileVertexShader);
  const std::string fragmentShaderSource = readFile(fileFragmentShader);
  const std::string fragmentShaderSource2 = readFile(fileFragmentShader2);
  shader1.createShaderProgram(vertexShaderSource,fragmentShaderSource);
  shader2.createShaderProgram(vertexShaderSource,fragmentShaderSource2);
  shader1.useShader();
  Object triangulo(trianguloGeometry,shader2);
  Object triangulo2(trianguloGeometry2,shader2);
  Object triangulo3(trianguloGeometry3,shader2);
  sceneObjects.push_back(triangulo);
  sceneObjects.push_back(triangulo2);
  sceneObjects.push_back(triangulo3);

  VAO = triangulo.getVAO();
  VAO2 = triangulo2.getVAO();
  VAO3 = triangulo3.getVAO();

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
  shader2.setUniform("fade",&greenValue);
  shader1.setUniform("color",color);
  shader1.setUniform("prueba",&prueba);
  for(int i=0; i<sceneObjects.size(); i++)
  {
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

std::string readFile(std::string& dir)
{
  std::ifstream file{dir};
  std::string const fileContent = static_cast<std::ostringstream&>
      (std::ostringstream{} << file.rdbuf()).str();
  return fileContent;
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
