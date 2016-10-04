
#version 450 compatibility

in vec3 interpolatedCol;
in vec2 interpolatedTex;
in vec3 Inormales;
in vec3 toLight[20];
in vec3 toCamera;
in vec3 colorI;

 uniform sampler2D diffuse;
 uniform sampler2D opacity;
 uniform sampler2D normalMap;

uniform int lightNumber;
uniform vec3 lightPos[20];
uniform vec3 lightColor[20];
uniform float lightIntensity[20];
uniform vec3 attenuation[20];
uniform vec3 camPos;
uniform float shineDamping;
uniform float reflectivity;

out vec4 color;





void main(){


vec4 ambiant=vec4(0.1,0.4,0.3,1.0);
vec3 unitNormal=normalize(2.0 * texture2D(normalMap,interpolatedTex).rgb - 1.0 ) ;
vec3 total=vec3(0.0);
vec3 unitToCamera=normalize(toCamera);
vec3 finalSpec=vec3(0.0);


for(int i=0;i<lightNumber;i++){
float dist = length(toLight[i]);

float attenuationFact=attenuation[i].x+(attenuation[i].y*dist)+(attenuation[i].z*dist*dist);	

vec3 unitToLight=normalize(toLight[i]);
vec3 unitFromLight= - unitToLight;

vec3 reflectedLight=reflect(unitFromLight,Inormales);
float specular= max(dot(reflectedLight,unitToCamera),0.0F);
float damping= pow(specular,shineDamping);
finalSpec += damping*lightColor[i]*reflectivity;
float brightness=clamp(dot(unitNormal,unitToLight),0.0,1.0);
vec3 diffuse= brightness * lightColor[i]*(lightIntensity[i]);
total+=diffuse/attenuationFact;
}

vec4 tex=texture2D(diffuse,interpolatedTex)/3;
vec4 op=texture2D(opacity,interpolatedTex);


if(op.rgb!=vec3(1,1,1)){

	//color=vec4(total,1.0)*tex;
	color=mix(vec4(total,1.0),tex,0.5);
}
else
discard;
}