#type vertex
#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;

uniform mat4 u_VP;

out vec2 texCoord;

void main()
{
    gl_Position = u_VP * vec4(a_Pos, 1.0);
    texCoord = a_TexCoord;
}

#endtype vertex
#type fragment
#version 410 core

in vec2 texCoord;

out vec4 fragmentColor;

uniform sampler2D u_Diffuse;
uniform sampler2D u_Specular;
uniform sampler2D u_Normal;
uniform sampler2D u_Height;

void main()
{
    fragmentColor = texture(u_Diffuse, texCoord);
}

#endtype fragment