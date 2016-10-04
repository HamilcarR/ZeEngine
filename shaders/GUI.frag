#version 450 compatibility



uniform sampler2D diffuse;

in vec3 interpolatedCol;
in vec2 interpolatedTex;
in vec3 Inormales;
in vec3 toCamera;
in vec3 colorI;



layout(location=0) out vec4 color;

void main(void){



color=texture2D(diffuse,interpolatedTex);
}