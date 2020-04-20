#type vertex
#version 410 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec4 a_Color;
layout (location = 3) in float  a_TexID;

uniform mat4 u_VP;
out vec4 fragmentColor;
out vec2 textCoord;
out float texID;

void main()
{
    gl_Position = /*u_VP **/ vec4(a_Pos, 1.0);
    fragmentColor = a_Color;
    texID = a_TexID;
    textCoord = a_TexCoord;
}

#endtype vertex
#type fragment
#version 410 core

in float texID;
in vec2 textCoord;
in vec4 fragmentColor;
out vec4 color;

uniform sampler2D u_TextureID[32];

void main()
{
    if(texID > 0)
        color = texture(u_TextureID[int(texID)], textCoord);
    else
        color = fragmentColor;
}

#endtype fragment