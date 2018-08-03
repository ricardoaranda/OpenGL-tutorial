#shader vertex
#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;

out vec3 Color;

void main()
{
   Color = color;
   gl_Position = position;
}

#shader fragment
#version 330

in vec3 Color;

out vec4 outColor;

void main()
{
   outColor = vec4(Color, 1.0);
}
