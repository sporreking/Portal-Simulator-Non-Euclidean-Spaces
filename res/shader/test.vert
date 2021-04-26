#version 430

// Uniform matrices
layout(location=0) uniform mat4 modelViewMat;
layout(location=1) uniform mat4 projectionMat;

// Uniform lighting
layout(location=1000) uniform uint nrLights;
layout(location=1032) uniform uint lightTypes[32];
layout(location=1064) uniform vec3 lightPositions[32];
layout(location=1096) uniform vec3 lightColors[32];
layout(location=1128) uniform double lightRanges[32];

// Attributes
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec3 in_TexCoords;

out vec4 pass_Color;
void main() {
    gl_Position = vec4(in_Position + lightPositions[0], 1.0);
    pass_Color = vec4(lightColors[0], lightRanges[0]);
}