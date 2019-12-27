#ifndef GAME_H_
#define GAME_H_
#include "stdio.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utilities.h"
#include "../Graphics/Geometry.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Object.h"
#include "../GameEntities/GameEntity.h"
#include "../GameEntities/Character.h"
#include "../GameEntities/Block.h"
#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Graphics/OrtographicCamera.h"
#include <tgmath.h>


enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
  GameState State;
  bool Keys[1024];
  int Width, Height;
  Game(int width,int height); //Constructor
  ~Game(); //Destructor

  void init();//Inicializador
  void render(); //Renderizador
  void update(float currentFrame,float time); //Actualizador del tiempo
  void processInput(float time); //Procesar entradas
private:
  void loadLevel();
  void armarTextura2(unsigned int* texture,unsigned char* data, int w, int h,int mode);
  float verticesQuad2[18] =
  {
    1.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f,
    1.0f,-1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f,
   -1.0f,-1.0f, 0.0f,
    1.0f,-1.0f, 0.0f
  };
  float texCoordsQuad2[12] =
  {
    1.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
  };
  Shader* shaderText2;
  Shader* shaderQuad2;
  std::string fileShaderText2 = "Shaders/shaderText.shader";
  std::string fileShaderQuad2 = "Shaders/shaderQuad.shader";
  std::vector<GameEntity*> levelObjects2;
  Object* genericQuad2;
  GameEntity* player2;
  FontManager* fontManager2;
  unsigned int texture2;
  OrtographicCamera* camera2;
  float timeValue2, greenValue2;
  float lastTimeFPS2 = 0;
  float currentFrame2;
  float deltaTime2;
  int indice2;
  std::string level2[6] =
  {
    "##############################################----##################################################",
    "##############################################----##################################################",
    "###########################################----------###############################################",
    "###############################################--###################################################",
    "###############################################--###################################################",
    "####################################################################################################",
  };
};
#endif
