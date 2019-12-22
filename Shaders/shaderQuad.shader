<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
  gl_Position = projection * view * transform * vec4(aPos, 1.0f);
}
<Shader>Fragment
#version 410 core
out vec4 FragColor;
uniform float fade;
void main()
{

  FragColor = vec4(fade,fade,0.0,1.0);
}
