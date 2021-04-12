#version 430

out vec4 out_Color;

in vec3 pass_Color;
void main() {
    out_Color = vec4(pass_Color, 1.0);
}