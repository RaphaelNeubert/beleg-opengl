#version 450 core  // 420, 330 core , compatibility
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec2 vTexture;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 u_ModelViewProjection;

void main(){
    //gl_Position = u_ModelViewProjection*vPosition;
    gl_Position = vPosition;
    Color = vColor;
    TexCoord = vTexture;
}
