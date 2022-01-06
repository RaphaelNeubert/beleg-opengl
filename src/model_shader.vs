#version 450 core  // 420, 330 core , compatibility
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexture;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main(){
    gl_Position = projection*view*model*vec4(vPosition,1.0f);
    Color = vColor;
    TexCoord = vTexture;
}
