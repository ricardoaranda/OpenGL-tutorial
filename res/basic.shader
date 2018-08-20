#shader vertex
#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 v_color;
out vec2 v_texCoord;

void main()
{
    gl_Position = position;
    v_color = color;
    v_texCoord = texCoord;
}

#shader fragment
#version 330

in vec3 v_color;
in vec2 v_texCoord;

uniform sampler2D u_Texture;

out vec4 outColor;

void main()
{
    vec4 texColor = texture(u_Texture, v_texCoord) * vec4(v_color, 1.0);
    outColor = texColor;
}
