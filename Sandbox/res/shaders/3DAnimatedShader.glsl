#type vertex
#version 410 core

#define MAX_BONES_COUNT 100

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in ivec4 a_BonesID;
layout (location = 4) in ivec4 a_Weights;

uniform mat4 u_VP;
uniform mat4 u_Bones[MAX_BONES_COUNT];

out vec2 texCoord;

void main()
{
    mat4 boneTransform = u_Bones[a_BonesID[0]] * a_Weights[0];

    for(int i = 1; i < 4; i++)
        boneTransform += u_Bones[a_BonesID[i]] * a_Weights[i];

    gl_Position = u_VP * boneTransform * vec4(a_Pos, 1.0);
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