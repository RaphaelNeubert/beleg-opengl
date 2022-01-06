#version 450 core  // 420, 330 core , compatibility
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexture;
layout(location = 3) in vec3 vNormal;
layout(location = 4) in mat4 vInstance;

out vec4 Color;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection*view*vInstance*vec4(vPosition,1.0f);
    Color = vColor;
    TexCoord = vTexture;
    Normal = vNormal;
    FragPos = vec3(vInstance*vec4(vPosition,1.0f));
}
