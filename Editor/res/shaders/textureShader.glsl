#type vertex
#version 430 core

layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec2 a_TexCoord;

uniform mat4 u_VP;

out vec2 texCoord;

void main()
{
    gl_Position = u_VP * vec4(a_Pos, 1.0);
    texCoord = a_TexCoord;
}

#endtype vertex
#type fragment
#version 430 core

in vec2 texCoord;
out vec4 fragmentColor;

uniform sampler2D u_TextureID;

void main()
{
    fragmentColor = texture(u_TextureID, texCoord);
}

#endtype fragment