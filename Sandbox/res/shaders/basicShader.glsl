#type vertex
#version 430 core
layout(location = 0) in vec3 a_Pos;
layout(location = 1) in vec4 a_Color;

out vec4 color;

void main()
{
    gl_Position = vec4(a_Pos, 1.0);
    color = a_Color;
}
#endtype vertex

#type fragment
#version 430 core

in vec4 color;

out vec4 fragmentColor;

void main()
{
    fragmentColor = color;
}

#endtype fragment