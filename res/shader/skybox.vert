#version 430

// Uniform matrices
layout(location=0) uniform mat4 modelMat;
layout(location=1) uniform mat4 viewMat;
layout(location=2) uniform mat4 projectionMat;

// Attributes
layout(location = 0) in vec3 in_Position;

out vec3 pass_TexCoords;

void main() {
    pass_TexCoords = in_Position;
    gl_Position = projectionMat * viewMat * modelMat * vec4(in_Position, 1);
}