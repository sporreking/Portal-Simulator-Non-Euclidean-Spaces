#version 430

// Uniform matrices
layout(location=0) uniform mat4 modelMat;
layout(location=1) uniform mat4 viewMat;
layout(location=2) uniform mat4 projectionMat;

// Uniform lighting
layout(location=1000) uniform uint nrLights;
layout(location=1032) uniform uint lightTypes[32];
layout(location=1064) uniform vec3 lightPositions[32];
layout(location=1096) uniform vec3 lightColors[32];
layout(location=1128) uniform float lightRanges[32];

// Attributes
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_TexCoords;

out vec3 pass_Position;
out vec3 pass_Normal;
out vec2 pass_TexCoords;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(in_Position, 1.0);
    pass_Position = (viewMat * modelMat * vec4(in_Position, 1.0)).xyz;
    
    mat3 normMat = transpose(inverse(mat3(viewMat * modelMat)));
	pass_Normal = normalize(normMat * in_Normal);

	pass_TexCoords = in_TexCoords;
}