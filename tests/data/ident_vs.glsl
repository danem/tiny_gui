#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvcoord;

out vec2 TexCoord;

void main () {
    gl_Position = vec4(position,1);
    TexCoord = vec2(uvcoord.x, 1 - uvcoord.y);
}
    
    