#shader vertex
#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * position;
    v_texCoord = texCoord;
}

#shader fragment
#version 330

in vec2 v_texCoord;

uniform sampler2D u_Texture;

out vec4 outColor;

void main()
{
    vec4 texColor = texture(u_Texture, v_texCoord);
    outColor = texColor;
}
