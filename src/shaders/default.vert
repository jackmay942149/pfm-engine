#version 330 core

layout (location = 0) in vec3 position;

uniform vec2 u_pos;

void
main() {
   gl_Position = vec4(u_pos.x + position.x, u_pos.y + position.y, position.z, 1.0);
}
