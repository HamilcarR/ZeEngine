#version 450 compatibility

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 color;
layout(location=2) in vec2 textureCoords;
layout(location=3) in vec3 normales;
layout(location=5) in vec3 tangents;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 cameraPosition;
uniform int lightNumber;

out vec3 interpolatedCol;
out vec2 interpolatedTex;
out vec3 colorI;


void main(){
gl_Position=model*vec4(vertex,1.0);
interpolatedCol=color;
interpolatedTex=textureCoords * vec2(1.0,1.0);


}

