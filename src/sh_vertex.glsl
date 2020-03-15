#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec4 adjust;
layout (location = 10) uniform mat4 model;
layout (location = 11) uniform mat4 view;
layout (location = 12) uniform mat4 projection;

out vec4 v_color;

void main(void) {
    gl_Position = (position * model * view * projection) + adjust;
    v_color = color;
}
