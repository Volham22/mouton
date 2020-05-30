#type vertex
#version 410 core

#define MAX_BONES_COUNT 20

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec2 a_TexCoord;
layout (location = 2) in vec3 a_Normal;
layout (location = 3) in ivec4 a_BonesID;
layout (location = 4) in vec4 a_Weights;

uniform mat4 u_Bones[MAX_BONES_COUNT];
uniform mat4 u_VP;

out vec2 texCoord;
out vec4 color;

void main()
{
    mat4 boneTransform = u_Bones[a_BonesID[0] > 0 ? a_BonesID[0] : 0] * a_Weights[0];
    boneTransform += u_Bones[a_BonesID[1] > 0 ? a_BonesID[1] : 0] * a_Weights[1];
    boneTransform += u_Bones[a_BonesID[2] > 0 ? a_BonesID[2] : 0] * a_Weights[2];
    boneTransform += u_Bones[a_BonesID[3] > 0 ? a_BonesID[3] : 0] * a_Weights[3];

    gl_Position = u_VP * boneTransform * vec4(a_Pos, 1.0);
    texCoord = a_TexCoord;

    if(a_BonesID[1] > 0)
        color = vec4(0.0, 1.0, 0.0, 1.0);
    else
        color = vec4(0.0, 0.0, 1.0, 1.0);
}

#endtype vertex
#type fragment
#version 410 core

in vec4 color;
in vec2 texCoord;

out vec4 fragmentColor;

uniform sampler2D u_Diffuse;
uniform sampler2D u_Specular;
uniform sampler2D u_Normal;
uniform sampler2D u_Height;

void main()
{
    // fragmentColor = texture(u_Diffuse, texCoord);
    fragmentColor = color;
}

#endtype fragment