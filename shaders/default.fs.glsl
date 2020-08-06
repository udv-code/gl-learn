#version 330 core

uniform sampler2D u_texture;

in vec3 color;
in vec2 texture_coord;

out vec4 o_color;

void main() {
    o_color = texture(u_texture, texture_coord);
}
