

#version 450 compatibility




layout(location=0) in vec3 position;




uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;



out vec3 textures;





void main(){


mat4 v=view;
v[3]=vec4(vec3(0.0),1.0);
gl_Position = projection*v*model*vec4(position,1.0);

textures=position;

}

