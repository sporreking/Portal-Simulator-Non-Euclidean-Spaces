#version 430

in vec2 pass_TexCoords;

layout(location=0) out vec4 out_Color;

void main() {
    out_Color = vec4(1, 1, 0, 1);
}