#version 410 core
out vec4 FragColor;
uniform float fade;
void main()
{

  FragColor = vec4(fade,fade,0.0,1.0);
}
