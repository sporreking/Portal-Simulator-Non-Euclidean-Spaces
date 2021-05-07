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

// Uniform Material
layout(location=2000) uniform float kd;
layout(location=2001) uniform float ks;
layout(location=2002) uniform float alpha;
layout(location=2003) uniform vec3 color;
layout(location=2004) uniform sampler2D tex;

// Attributes
layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec3 in_TexCoords;

in vec3 pass_Position;
in vec3 pass_Normal;
in vec2 pass_TexCoords;

layout(location=0) out vec4 out_Color;

// Constants
const float AMBIENT_STRENGTH = 0.1;
const vec3 AMBIENT_COLOR = vec3(1.0, 1.0, 1.0);

// Light types
#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1

void main() {
    
    vec3 normal = normalize(pass_Normal);

    // Ambient lighting
    vec3 intensity = AMBIENT_STRENGTH * AMBIENT_COLOR;

    // Handle light sources
    for (int i = 0; i < nrLights; i++) {
        // Diffuse lighting
        vec3 lightNorm;
        if (lightTypes[i] == LIGHT_TYPE_POINT)
            lightNorm = normalize((viewMat * vec4(lightPositions[i], 1)).xyz - pass_Position);
        else if (lightTypes[i] == LIGHT_TYPE_DIRECTIONAL)
            lightNorm = transpose(inverse(mat3(viewMat))) * lightPositions[i];

        float diffuse = clamp(dot(lightNorm, normal), 0, 1);

        // Specular Lighting
        vec3 reflectNorm = reflect(-lightNorm, normal);
        vec3 lookDirection = normalize(-pass_Position);

        float specularStrength = clamp(dot(reflectNorm, lookDirection), 0, 1);
        float specular = pow(max(specularStrength, 0.01), alpha);

        intensity += (kd * diffuse + ks * specular) * lightColors[i];
    }

    intensity = clamp(intensity, 0, 1);

    out_Color = vec4(intensity * color * texture(tex, pass_TexCoords).xyz, 1);
}