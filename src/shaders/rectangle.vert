#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 coords;

uniform vec2  u_pos;
uniform float u_width;
uniform float u_height;

out vec2 o_coords;

void
main() {
   o_coords = coords;
   gl_Position = vec4(u_pos.x + position.x * u_width/2, u_pos.y + position.y * u_height/2, position.z, 1.0);
}
