#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 adjust;

void main(void) {
    gl_Position = position + adjust;
}
