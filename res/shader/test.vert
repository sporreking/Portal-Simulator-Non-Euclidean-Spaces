#version 430

layout(location=0) in vec3 in_Position;
in vec3 in_Color;

out vec3 pass_Color;
void main() {
    gl_Position = vec4(in_Position, 1.0);

    pass_Color = in_Color;
}