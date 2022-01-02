#version 450 core  // 420, 330 core , compatibility
in vec4 Color;
in vec2 TexCoord;
layout(location=0) out vec4 fColor;

uniform sampler2D tex;

void main()
{
    fColor = Color;
    //fColor = Color*texture(tex, TexCoord);
}
