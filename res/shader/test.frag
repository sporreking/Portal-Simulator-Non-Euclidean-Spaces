#version 430

out vec4 out_Color;

in vec4 pass_Color;
void main() {
    out_Color = pass_Color;
}