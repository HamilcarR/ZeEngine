



#version 450 compatibility 

in vec2 texture_coord;
in vec3 normales_coord;
in vec3 CamPosition;
in vec3 toLight[20];



uniform sampler2D diffuse;
uniform sampler2D normalMap;
uniform int lightNumber;
uniform vec3 lightPos[20];
uniform vec3 lightColor[20];
uniform float lightIntensity[20];
uniform vec3 attenuation[20];
uniform float reflectivity;
uniform float shineDamping;

out vec4 color;


void main(){


vec3 normales=normalize(normales_coord);
vec3 camPos=normalize(CamPosition);

vec3 total=vec3(0.0);
vec3 specular=vec3(0.0);
for(int i=0;i<lightNumber;i++){

float dist=length(toLight[i]);
float attenuationFactor=attenuation[i].x + attenuation[i].y*dist + attenuation[i].z*dist*dist;
vec3 diffuse=lightIntensity[i]*lightColor[i];
float brightness=clamp(dot(normales,normalize(toLight[i])),0.0,1.0);

vec3 unitToLight=normalize(toLight[i]);
vec3 fromLight=-unitToLight;
vec3 reflected=reflect(fromLight,normales);

float result=max(dot(reflected,camPos),0.0F);

float damping=pow(result,shineDamping);

specular+=damping*lightColor[i]*reflectivity;
total+=brightness*diffuse/attenuationFactor;
}


color=vec4(total,1.0)*(texture2D(diffuse,texture_coord));
}