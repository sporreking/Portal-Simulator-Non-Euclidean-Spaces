#version 430

// Uniform cubemap
layout(location=2003) uniform vec3 color;
layout(location=2004) uniform samplerCube skybox;

// Attributes
in vec3 pass_TexCoords;

layout(location=0) out vec4 out_Color;

void main() {
    out_Color = vec4(color * texture(skybox, pass_TexCoords).xyz, 1);
}