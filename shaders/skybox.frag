





#version 450 compatibility

in vec3 textures;


uniform samplerCube sampler;


out vec4 color;



void main(){


vec3 tex=normalize(textures);
color= texture(sampler,tex);
}