#version 330 core

in vec2 o_coords;

out vec4 out_colour;

uniform sampler2D texture1;

void
main() {
  vec4 temp = texture(texture1, o_coords);
  out_colour = vec4(temp.rgba);
}
