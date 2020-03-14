#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec4 adjust;

out vec4 v_color;

void main(void) {
    gl_Position = position + adjust;
    v_color = color;
}
