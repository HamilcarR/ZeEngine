

#version 450 compatibility

#define X 0.111
#define Y 0.999

uniform sampler2D diffuse;
uniform sampler2D texture1;
uniform sampler2D normalMap;
uniform sampler2D DUDV;
uniform float time;
uniform int lightNumber;
uniform vec3 lightPos[20];
uniform vec3 lightColor[20];
uniform float lightIntensity[20];
 vec3 attenuation[20];
uniform vec3 camPos;
 const float shineDamping=1.F;
 const float reflectivity=0.1F;



in vec4 modelview;
in vec3 Inormales;
in vec3 toLight[20];
in vec3 toCamera;
in vec3 colorI;
in vec2 tex;
in vec3 posCamera;
in mat4 modelOut;



out vec4 color;


const float att=0.009; 


void main(void){

 float x=(modelview.x/modelview.w) / 2. + 0.5;
 float y=(modelview.y/modelview.w)/ 2. + 0.5;
 
 float disx=(texture2D(DUDV,tex + time)*2. - 1.).r*att; 
 float disy=(texture2D(DUDV,tex - time)*2. - 1.).g*att; 

 vec2 dis = vec2(disx,-disy);
 vec2 tex1 = vec2 (x,y) + dis ;
 vec2 tex2 = vec2 (x,-y) + dis ;
 vec4 reflection=texture2D(diffuse,tex2);
 vec4 refraction=texture2D(texture1,tex1);

vec4 ambiant=vec4(0.1,0.4,0.3,1.0);
vec3 un=normalize((2.0 * texture2D(normalMap,tex+time).rgb - 1.0 )*att)  ;
vec3 unitNormal = vec3(un.r,un.g,un.b) ;
vec3 total=vec3(0.0);
vec3 unitToCamera=normalize(toCamera); 
vec3 finalSpec=vec3(0.0);
vec3 var=vec3(0.);
vec3 toCameraMspace = normalize(posCamera);




for(int i=0;i<lightNumber;i++){
attenuation[i] = vec3(1,1*10,1*100);
float dist = length(toLight[i]);

float attenuationFact=attenuation[i].x+(attenuation[i].y*dist)+(attenuation[i].z*dist*dist);	

vec3 unitToLight=normalize(toLight[i]);
vec3 unitFromLight= - unitToLight;

vec3 reflectedLight=reflect(unitFromLight,unitNormal);
float specular= max(dot(reflectedLight,posCamera),0.0F);
float damping= pow(specular,shineDamping);
finalSpec += damping*lightColor[i]*reflectivity;
float brightness=clamp(dot(unitNormal,unitToLight),0.0,1.0);
vec3 diff= brightness * lightColor[i]*(lightIntensity[i]);
total+=diff/attenuationFact;

}

 float fresnel = clamp(dot(vec3(0.,1.,0.),toCameraMspace),0.5,0.9); 
 fresnel = pow (fresnel, 1.); 
 //color= vec4(un,1.);
 color=mix(reflection,refraction, fresnel )+vec4(0.,0.1,0.15,1.) ;//+ vec4(finalSpec,1.);
 //color= texture(diffuse , tex ) ; 
}


