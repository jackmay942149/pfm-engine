#version 330 core

layout (location = 0) in vec3 position;

// Top Left = {-0.1, 0.1}

uniform vec2  u_pos;
uniform float u_width;
uniform float u_height;

void
main() {
   gl_Position = vec4(u_pos.x + position.x * u_width/2, u_pos.y + position.y * u_height/2, position.z, 1.0);
}
