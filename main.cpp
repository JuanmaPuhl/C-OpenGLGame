#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <map>
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
#include "OrtographicCamera.h"
#include FT_FREETYPE_H

/*Declaraciones previas de funciones implementadas mas abajo*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();
void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
std::vector<Object> sceneObjects;
std::vector<Shader> shaders;
/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    int Advance;    // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
GLuint VAO, VBO;
FT_Library library;
FT_Face face;
std::string fileVertexShader = "Shaders/vs.glsl";
std::string fileVertexShader2 = "Shaders/vs2.glsl";
std::string fileFragmentShader = "Shaders/fs.glsl";
std::string fileFragmentShader2 = "Shaders/fs2.glsl";
const int WIDTH = 1280;
const int HEIGHT = 720;
Game Game(WIDTH, HEIGHT);
float color[3] = {0.1,0.7,0.5};
float prueba = 1.0f;
float vertices[] =
{
  1.0f, 1.0f, 0.0f,
 -1.0f, 1.0f, 0.0f,
  1.0f,-1.0f, 0.0f,
 -1.0f, 1.0f, 0.0f,
 -1.0f,-1.0f, 0.0f,
  1.0f,-1.0f, 0.0f
};
// int fps = 0;
// int fpsConstante = 0;
float timeValue, greenValue;
float lastTimeFPS = 0;
float currentFrame;
int indice;
OrtographicCamera camera(WIDTH,HEIGHT);

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
  glViewport(0, 0, WIDTH, HEIGHT);
  //glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  Game.init();
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;
  Game.State = GAME_ACTIVE;
  Geometry quadGeometry(vertices,NELEMS(vertices));
  Shader shader1(fileVertexShader,fileFragmentShader);
  Shader shader2(fileVertexShader2,fileFragmentShader2);
  shaders.push_back(shader1);
  shaders.push_back(shader2);
  shader1.useShader();
  Object player(quadGeometry,shader2);
  player.scale(glm::vec3(100.0,100.5,1.0));
  player.setPosition(glm::vec3(float(WIDTH / 2),float(HEIGHT/2),0.0f));
  sceneObjects.push_back(player);

  // FreeType
  FT_Library ft;
  // All functions return a value different than 0 whenever an error occurred
  if (FT_Init_FreeType(&ft))
      std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  // Load font as face
  FT_Face face;
  if (FT_New_Face(ft, "Fonts/Minecraft.ttf", 0, &face))
      std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

  // Set size to load glyphs as
  FT_Set_Pixel_Sizes(face, 0, 48);

  // Disable byte-alignment restriction
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Load first 128 characters of ASCII set
  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_RED,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Now store character for later use
    Character character = {
        texture,
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x
    };
    Characters.insert(std::pair<GLchar, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  // Destroy FreeType once we're finished
  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  // Configure VAO/VBO for texture quads
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window))
  {
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    Game.processInput(deltaTime);
    // debug.getFpsCount(currentFrame,&lastTimeFPS);
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
  shaders[0].useShader();
  RenderText(shaders[0], "FPS: ", 3.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));
  RenderText(shaders[0], std::to_string(debug.getFpsCount(currentFrame,&lastTimeFPS)), 53.0f, 3.0f, 0.4f, glm::vec3(1.0f, 1.0f, 1.0f));

  for(int i=0; i<sceneObjects.size(); i++)
  {
    sceneObjects[i].getShader().useShader();
    sceneObjects[i].getShader().setUniform("view",glm::value_ptr(camera.getViewMatrix()));
    sceneObjects[i].getShader().setUniform("projection",glm::value_ptr(camera.getProjectionMatrix()));
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
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.moveCamera(-1);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.moveCamera(1);
  }
}

void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color)
{
    // Activate corresponding render state
    shader.useShader();
    shader.setUniform("projection",glm::value_ptr(camera.getProjectionMatrix()));
    shader.setUniform("textColor",glm::value_ptr(color));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y + (Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
          { xpos,     ypos + h,   0.0, 1.0 },
          { xpos + w, ypos,       1.0, 0.0 },
          { xpos,     ypos,       0.0, 0.0 },

          { xpos,     ypos + h,   0.0, 1.0 },
          { xpos + w, ypos + h,   1.0, 1.0 },
          { xpos + w, ypos,       1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
