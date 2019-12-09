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
#include <ft2build.h>
#include FT_FREETYPE_H


/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void getFpsCount(float current,float* lastTime);
std::string readFile(std::string& dir);
void printTextScreen(int x, int y, std::string str);

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
unsigned int VBO,VBO2,VBO3;
float color[3] = {1.0f,0.0f,0.0f};
int prueba = 2;
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
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glGenBuffers(1, &VBO3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
  const std::string vertexShaderSource = readFile(fileVertexShader);
  const std::string fragmentShaderSource = readFile(fileFragmentShader);
  const std::string fragmentShaderSource2 = readFile(fileFragmentShader2);
  shader1.createShaderProgram(vertexShaderSource,fragmentShaderSource);
  shader2.createShaderProgram(vertexShaderSource,fragmentShaderSource2);
  shader1.useShader();
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glGenVertexArrays(1, &VAO2);
  glBindVertexArray(VAO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glGenVertexArrays(1, &VAO3);
  glBindVertexArray(VAO3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    getFpsCount(currentFrame,&lastTimeFPS);
    Game.update(deltaTime);
    render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

void getFpsCount(float current,float* lastTime)
{
  fps++;
  if((current - *lastTime) >= 1.0f)
  {
    double fpsCount = 1000.0/double(fps);
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "MS: " << fpsCount <<std::endl;
    fps = 0;
    (*lastTime)++;
  }
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
  shader2.useShader();
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/sizeof(*vertices) / 3);
  glBindVertexArray(VAO2);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices2)/sizeof(*vertices2) / 3);
  glBindVertexArray(VAO3);
  glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices3)/sizeof(*vertices3) / 3);
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
