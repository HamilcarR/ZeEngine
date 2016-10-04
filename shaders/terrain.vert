

#version 450 compatibility

 layout(location=0) in vec3 vertex;
 layout(location=1) in vec2 tex_coord;
 layout(location=2) in vec3 normales;




uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform int lightNumber;
uniform vec3 lightPos[20];


out vec2 texture_coord;
out vec3 normales_coord;
out vec3 CamPosition;
out vec3 toLight[20];

void main(){

gl_Position= (projection*view*model*vec4(vertex,1.0));

texture_coord=tex_coord*40.0;

//normales_coord=(model*vec4(normales,1.0)).xyz;
normales_coord=(vec4(normales,1.0)).xyz;
 CamPosition=(inverse(view)*vec4(vec3(0.0),1.0)).xyz - (model*vec4(vertex,1.0)).xyz;

for(int i=0;i<lightNumber;i++)
toLight[i]=lightPos[i]-(model*vec4(vertex,1.0)).xyz;






}