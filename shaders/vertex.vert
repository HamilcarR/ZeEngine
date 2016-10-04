
#version 450 compatibility

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 color;
layout(location=2) in vec2 textureCoords;
layout(location=3) in vec3 normales;
layout(location=5) in vec3 tangents;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos[20];
uniform vec3 lightColor[20];
uniform vec3 cameraPosition;
uniform int lightNumber;
uniform vec4 plane;

//const vec4 plane=vec4(0,1,0,-1);
out vec3 interpolatedCol;
out vec2 interpolatedTex;
out vec3 Inormales;
out vec3 toLight[20];
out vec3 toCamera;
out vec3 colorI;



void main(){
vec4 worldP=vec4(vertex,1.0);
gl_Position=projection*view*model*worldP;
interpolatedCol=color;
interpolatedTex=textureCoords * vec2(1.0,-1.0);


gl_ClipDistance[0]=dot(worldP,plane);

Inormales=(model*vec4(normales,0.0)).xyz;

colorI=color;



vec3 norm=normalize(Inormales);
vec3 tang=normalize( (model*vec4(tangents,1.0)).xyz);

vec3 bitang=normalize(cross (norm,tang));

mat3 TANGENT_SPACE= mat3( tang.x , bitang.x , norm.x ,
					  tang.y , bitang.y , norm.y ,
					  tang.z , bitang.z , norm.z );


for(int i=0;i<lightNumber;i++)
	 toLight[i]=TANGENT_SPACE * (lightPos[i] - (model*vec4(vertex,1.0)).xyz);

toCamera=TANGENT_SPACE*((inverse(view)*vec4(0.0,0.0,0.0,1.0)).xyz - (model*vec4(vertex,1.0)).xyz);



}

