#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Game::Game(int width, int height)
  :State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}
Game::~Game()
{
  std::cout<<"Entro a eliminar el game"<<std::endl;
  delete this->shaderText;
  delete this->shaderQuad;
  delete this->camera;
  delete this->player;

  for(unsigned int texture : textures)
  {
    delete &texture;
  }

  for(GameEntity* entity : levelObjects)
  {
    delete entity;
  }
}

void Game::init()
{
  this->camera = new OrtographicCamera(this->Width,this->Height);
  Geometry quadGeometry(this->verticesQuad,18,this->texCoordsQuad,12);
  this->shaderText = new Shader(this->fileShaderText);
  this->shaderQuad = new Shader(this->fileShaderQuad);
  this->genericQuad = new Object(quadGeometry,*shaderQuad);
  stbi_set_flip_vertically_on_load(true);
  this->textures.push_back(this->createTexture("Textures/pj.png",1));
  this->textures.push_back(this->createTexture("Textures/grass.png",1));
  loadLevel();
  this->player = new Character(*this->genericQuad,glm::vec2(32.0),glm::vec3(0.0),this->textures[0]);
  this->fontManager = new FontManager();
  (*this->genericQuad).getShader().useShader();
  glUniform1i(glGetUniformLocation(this->shaderQuad->getShaderProgram(), "image"), 0);

}

void Game::render()
{
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->camera->followEntity(this->player);
  (*this->camera).updateCamera(this->deltaTime);
  this->timeValue = glfwGetTime();
  this->greenValue= ((sin(this->timeValue) / 2.0f) + 0.5f);
  this->shaderText->useShader();
  this->shaderText->setUniform("projection",glm::value_ptr((*this->camera).getHUDProjectionMatrix()));
  this->fontManager->RenderText(*this->shaderText, "FPS: ", 3.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  this->fontManager->RenderText(*this->shaderText, std::to_string(debug.getFpsCount(this->currentFrame,&this->lastTimeFPS)), 53.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  this->player->getShader().useShader();
  this->player->getShader().setUniform("view",glm::value_ptr((*this->camera).getViewMatrix()));
  this->player->getShader().setUniform("projection",glm::value_ptr((*this->camera).getProjectionMatrix()));
  this->player->render(this->deltaTime);

  for(GameEntity* entidad : this->levelObjects)
  {
    entidad->getShader().useShader();
    entidad->getShader().setUniform("view",glm::value_ptr((*this->camera).getViewMatrix()));
    entidad->getShader().setUniform("projection",glm::value_ptr((*this->camera).getProjectionMatrix()));
    entidad->render(this->deltaTime);
  }
}

void Game::update(float currentFrame, float time)
{
  this->currentFrame = currentFrame;
  this->deltaTime = time;
}
void Game::processInput(float time)
{
  glm::vec2 direction = glm::vec2(0.0);
  if (this->Keys[GLFW_KEY_A])
    direction[0] = -1;
  if (this->Keys[GLFW_KEY_D])
    direction[0] = 1;
  if(!this->Keys[GLFW_KEY_A] && !this->Keys[GLFW_KEY_D])
    direction[0] = 0;
  if (this->Keys[GLFW_KEY_W])
    direction[1] = 1;
  if (this->Keys[GLFW_KEY_S])
    direction[1] = -1;
  if(!this->Keys[GLFW_KEY_W] && !this->Keys[GLFW_KEY_S])
    direction[1] = 0;
  static_cast<Character*>(this->player)->move(direction);

  if(this->Keys[GLFW_KEY_U])
    this->camera->zoomCamera(1);
  if(this->Keys[GLFW_KEY_J])
    this->camera->zoomCamera(-1);
  if(!this->Keys[GLFW_KEY_U] && !this->Keys[GLFW_KEY_J])
    this->camera->zoomCamera(0.0);


  if(this->Keys[GLFW_KEY_F])
    this->camera->moveCamera(1);
  if(this->Keys[GLFW_KEY_G])
    this->camera->moveCamera(-1);
  if(!this->Keys[GLFW_KEY_F] && !this->Keys[GLFW_KEY_G])
    this->camera->moveCamera(0);
}

void Game::loadLevel()
{
  float x = 0.0f;
  float y = 0.0f;
  int contador = 0;
  this->levelObjects.push_back(new Block(*this->genericQuad,glm::vec2(512.0),glm::vec3(0.0,0.0, -0.3),glm::vec3(0.42,0.63,0.27),false));
  for(int i=0; i<NELEMS(this->level); i++)
  {
    std::string linea = this->level[i];
    for(int j=0; j<linea.length(); j++)
    {
      contador++;
      if(linea.at(j)=='#')
      {
        float positionX = x-(linea.length()/2)*this->TILEWIDTH;
        float positionY = y+(NELEMS(this->level)/2)*this->TILEHEIGHT;
        float positionZ = -0.1f;
        glm::vec3 position = glm::vec3(positionX,positionY,positionZ);
        glm::vec2 objectSize = glm::vec2(this->TILEWIDTH,this->TILEHEIGHT);
        Object object = *this->genericQuad;
        unsigned int texture = this->textures[1];
        GameEntity* block = new Block(object,objectSize,position,texture,false);
        this->levelObjects.push_back(block);
      }
      x += this->TILEWIDTH;
    }
    y -= this->TILEHEIGHT;
    x = 0.0f;
  }
}

void Game::armarTextura(unsigned int* texture,unsigned char* data, int w, int h,int mode)
{
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  if(mode)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Game::createTexture(std::string imageDir, int mode)
{
  int w, h, nrChannels;
  unsigned int texture;
  unsigned char *data = stbi_load(imageDir.c_str(), &w, &h, &nrChannels, 0);
  if (data)
  {
    this->armarTextura(&texture,data,w,h,mode);
  }
  stbi_image_free(data);
  return texture;
}
