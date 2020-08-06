#version 330 core

in vec3 color;

out vec4 o_color;

void main() {
    o_color = vec4(color.rgb, 1.0f);
}
