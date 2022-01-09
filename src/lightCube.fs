#version 450 core  // 420, 330 core , compatibility
layout(location=0) out vec4 fColor;

uniform vec3 lightColor;
void main()
{
    fColor = vec4(lightColor, 1.0);
}
