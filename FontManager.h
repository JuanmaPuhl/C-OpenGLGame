#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <ft2build.h>
#include "Shader.h"
#include FT_FREETYPE_H

void fontManagerInit();
void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
#endif
