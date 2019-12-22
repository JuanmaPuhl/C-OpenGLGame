<Shader>Vertex
#version 410 core
layout (location = 0) in vec4 aPos;
out vec2 TexCoords;
uniform mat4 projection;
void main()
{
  gl_Position = projection * vec4(aPos.xy,0.0, 1.0f);
  TexCoords = aPos.zw;
}
<Shader>Fragment
#version 410 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
