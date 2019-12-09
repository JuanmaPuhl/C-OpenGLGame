#version 410 core
out vec4 FragColor;
uniform vec3 color;
uniform float prueba;
void main()
{
  FragColor = vec4(color,1.0);
}
