#include "Game.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Game::Game(int width, int height)
  :State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}
Game::~Game()
{

}

void Game::init()
{
  this->camera2 = new OrtographicCamera(this->Width,this->Height);
  Geometry quadGeometry2(this->verticesQuad2,18,this->texCoordsQuad2,12);
  this->shaderText2 = new Shader(this->fileShaderText2);
  this->shaderQuad2 = new Shader(this->fileShaderQuad2);
  this->genericQuad2 = new Object(quadGeometry2,*shaderQuad2);
  loadLevel();
  this->player2 = new Character(*this->genericQuad2,glm::vec2(32.0),glm::vec3(0.0),glm::vec3(0.8,0.0,0.80));
  this->fontManager2 = new FontManager();
  glGenTextures(1, &this->texture2);
  int w, h, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load("Textures/pj.png", &w, &h, &nrChannels, 0);
  if (data)
  {
    this->armarTextura2(&this->texture2,data,w,h,1);
  }
  (*this->genericQuad2).getShader().useShader();
  glUniform1i(glGetUniformLocation(this->shaderQuad2->getShaderProgram(), "image"), 0);
  stbi_image_free(data);
}

void Game::render()
{
  glClearColor(0.0f,0.0f,0.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  this->timeValue2 = glfwGetTime();
  this->greenValue2= ((sin(this->timeValue2) / 2.0f) + 0.5f);
  (*this->camera2).refreshViewMatrix();
  this->shaderText2->useShader();
  this->shaderText2->setUniform("projection",glm::value_ptr((*this->camera2).getHUDProjectionMatrix()));
  this->fontManager2->RenderText(*this->shaderText2, "FPS: ", 3.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  this->fontManager2->RenderText(*this->shaderText2, std::to_string(debug.getFpsCount(this->currentFrame2,&this->lastTimeFPS2)), 53.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  this->player2->getShader().useShader();
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, texture1);
  this->player2->getShader().setUniform("view",glm::value_ptr((*this->camera2).getViewMatrix()));
  this->player2->getShader().setUniform("projection",glm::value_ptr((*this->camera2).getProjectionMatrix()));
  this->player2->render();
  for(GameEntity* entidad : this->levelObjects2)
  {
    entidad->getShader().useShader();
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, texture1);
    entidad->getShader().setUniform("view",glm::value_ptr((*this->camera2).getViewMatrix()));
    entidad->getShader().setUniform("projection",glm::value_ptr((*this->camera2).getProjectionMatrix()));
    entidad->render();
  }
}

void Game::update(float currentFrame, float time)
{
  this->currentFrame2 = currentFrame;
  this->deltaTime2 = time;
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
  static_cast<Character*>(this->player2)->move(direction);

  if(this->Keys[GLFW_KEY_U])
    this->camera2->zoomCamera(1);
  if(this->Keys[GLFW_KEY_J])
    this->camera2->zoomCamera(-1);
  if(!this->Keys[GLFW_KEY_U] && !this->Keys[GLFW_KEY_J])
    this->camera2->zoomCamera(0.0);


  if(this->Keys[GLFW_KEY_F])
    this->camera2->moveCamera(1);
  if(this->Keys[GLFW_KEY_G])
    this->camera2->moveCamera(-1);
  if(!this->Keys[GLFW_KEY_F] && !this->Keys[GLFW_KEY_G])
    this->camera2->moveCamera(0);
}

void Game::loadLevel()
{
  float x = 0.0f;
  float y = 0.0f;
  int contador = 0;
  for(int i=0; i<NELEMS(this->level2); i++)
  {
    std::string linea = this->level2[i];

    for(int j=0; j<linea.length(); j++)
    {
      contador++;
      if(linea.at(j)=='#')
      {
        std::cout<<"#";
        this->levelObjects2.push_back(new Block(*this->genericQuad2,glm::vec2(32.0),glm::vec3(x-(linea.length()/2)*64.0f,y+(NELEMS(this->level2)/2)*64.0f,-0.1),glm::vec3(i/100.0+0.2,0.0,j/100.0+0.2),false));
      }
      else
        std::cout<<"-";
      x += 64.0f;

    }
    std::cout<<std::endl;
    y -= 64.0f;
    x = 0.0f;
    // std::cout<<linea<<std::endl;
  }
  std::cout<<contador<<std::endl;
}

void Game::armarTextura2(unsigned int* texture,unsigned char* data, int w, int h,int mode)
{
  glBindTexture(GL_TEXTURE_2D, *texture);
  if(mode)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
}
