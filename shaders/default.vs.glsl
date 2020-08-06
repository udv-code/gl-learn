#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;

out vec3 color;

void main() {
    gl_Position = vec4(a_pos.xyz, 1.0f);
    color = a_color;
}
