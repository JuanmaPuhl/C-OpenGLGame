#version 410 core
out vec4 FragColor;
uniform vec3 color;
uniform int prueba;
void main()
{
  FragColor = vec4(color.x,prueba,color.z, 1.0f);
}
