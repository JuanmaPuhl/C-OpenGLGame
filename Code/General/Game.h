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
  unsigned int createTexture(std::string imageDir, int mode);
  void loadLevel();
  void armarTextura(unsigned int* texture,unsigned char* data, int w, int h,int mode);
  float verticesQuad[18] =
  {
    0.5f, 0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f,
    0.5f,-0.5f, 0.0f,
   -0.5f, 0.5f, 0.0f,
   -0.5f,-0.5f, 0.0f,
    0.5f,-0.5f, 0.0f
  };
  float texCoordsQuad[12] =
  {
    1.0f, 1.0f,
    0.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
  };
  Shader* shaderText;
  Shader* shaderQuad;
  std::string fileShaderText = "Shaders/shaderText.shader";
  std::string fileShaderQuad = "Shaders/shaderQuad.shader";
  std::vector<GameEntity*> levelObjects;
  Object* genericQuad;
  GameEntity* player;
  FontManager* fontManager;
  OrtographicCamera* camera;
  float timeValue, greenValue;
  float lastTimeFPS = 0;
  float currentFrame;
  float deltaTime;
  int indice;
  std::vector<unsigned int> textures;
  std::string level[6] =
  {
    "------------------------------------------------------------------------------------------------####",
    "------------------------------------------------------------------------------------------------####",
    "---------------------------------------------------------------------------------------------------#",
    "----------------------------------------------#------------------------------------------------#####",
    "----------------------------------------------#------------------------------------------------#####",
    "--------------------------------------------------------------------------------------------########",
  };
  float TILEHEIGHT = 32.0f;
  float TILEWIDTH = 32.0f;
};
#endif
