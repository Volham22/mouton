#type vertex
#version 430 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in int  a_TexID;

uniform mat4 u_VP;
out vec4 fragmentColor;

void main()
{
    gl_Position = u_VP * vec4(a_Pos, 1.0);
    fragmentColor = a_Color;
}

#endtype vertex
#type fragment
#version 410 core

in vec4 fragmentColor;
out vec4 color;

void main()
{
    color = fragmentColor;
}

#endtype fragment