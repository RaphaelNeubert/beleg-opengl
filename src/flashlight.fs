#version 450 core  // 420, 330 core , compatibility
in vec4 Color;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
layout(location=0) out vec4 fColor;

uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 direction;
uniform float angleOpen; //as cos(angle)
uniform float outerAngleOpen; //as cos(angle)

void main()
{
    vec3 ambient=lightColor*0.1;
    vec3 lightDir=normalize(lightPos-FragPos);

    float angle=dot(lightDir, normalize(-direction)); //as cos(angle)

    //diffuse
    float diff=max(dot(Normal,lightDir),0.0); 
    vec3 diffuse=diff*lightColor;

    //attenuation
    float d=length(lightPos-FragPos);
    float attenuation=1.0/(1.0+0.014*d+0.0007*(d*d));
    diffuse*=attenuation;
    
    //specular
    float strength=0.5;
    vec3 viewDir=normalize(lightPos-FragPos); //lightPos=viewPos
    vec3 reflectDir=reflect(-lightDir,Normal); 
    float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular=strength*spec*lightColor;  

    //soft edges & dark outside cone
    float epsilon=angleOpen-outerAngleOpen;
    //clamp makes sure it's 0 when < 0 and 1 if > 1
    float intensity=clamp((angle-outerAngleOpen)/epsilon, 0.0, 1.0);    
    diffuse*=intensity;

    fColor = texture(tex, TexCoord)*Color*vec4((ambient+diffuse+specular),1.0);
}
