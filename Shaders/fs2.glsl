#version 410 core
out vec4 FragColor;
uniform float fade;
void main()
{

  FragColor = vec4(0.0,fade,0.0,1.0);
}
