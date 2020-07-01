#type vertex
#version 430 core
layout(location = 0) in vec3 a_Pos;

uniform mat4 u_VP;

void main()
{
    gl_Position = u_VP * vec4(a_Pos, 1.0);
}
#endtype vertex

#type fragment
#version 430 core

uniform vec4 u_Color;

out vec4 fragmentColor;

void main()
{
    fragmentColor = u_Color;
}

#endtype fragment