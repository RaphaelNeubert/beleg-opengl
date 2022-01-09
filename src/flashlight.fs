#version 450 core  // 420, 330 core , compatibility
in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
layout(location=0) out vec4 fColor;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform float angleOpen; //as cos(angle)

void main()
{
    vec3 ambient=lightColor*0.1;
    vec3 direction=normalize(lightPos-FragPos);

    float angle=dot(direction, normalize(-lightDir));

    if (angle > angleOpen) {
        //angle between norm and direction 
        float diff=max(dot(Normal,direction),0.0); 
        vec3 diffuse=diff*lightColor;

        fColor = texture(tex, TexCoord)*Color*vec4((ambient+diffuse),1.0);
    }
    else {
        fColor = texture(tex, TexCoord)*Color*vec4(ambient,1.0);
    }
}
