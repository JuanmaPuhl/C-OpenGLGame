#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <ft2build.h>
#include "../Graphics/Shader.h"
#include FT_FREETYPE_H
class FontManager
{
public:
  FontManager();
  ~FontManager();
  void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
  /// Holds all state information relevant to a character as loaded using FreeType
  struct Character {
      GLuint TextureID;   // ID handle of the glyph texture
      glm::ivec2 Size;    // Size of glyph
      glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
      int Advance;    // Horizontal offset to advance to next glyph
  };

  std::map<GLchar, Character> Characters;
  GLuint VAOText, VBOText;
};

#endif
