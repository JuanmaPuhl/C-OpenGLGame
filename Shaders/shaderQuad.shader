<Shader>Vertex
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 textureCoords;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
out vec2 texCoords;
void main()
{
  texCoords = textureCoords;
  gl_Position = projection * view * transform * vec4(aPos, 1.0f);
}
<Shader>Fragment
#version 410 core
in vec2 texCoords;
out vec4 FragColor;
uniform vec3 color;
uniform sampler2D image;
void main()
{
  //FragColor = vec4(texCoords.xy,0.0,1.0);
  //FragColor = vec4(color.xyz,1.0);
  vec4 color = texture(image,texCoords);//+vec4(0.5,0.0,0.0,1.0);

  if(color.a < 0.1)
  {
    discard;
  }
  FragColor = color;
}
