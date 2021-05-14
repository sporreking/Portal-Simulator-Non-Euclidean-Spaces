#version 430

// Uniforms
layout(location=2003) uniform vec3 color;
layout(location=2004) uniform sampler2D tex;

layout(location=3001) uniform bool useTexture;
layout(location=3002) uniform bool useMinDepth;
layout(location=3003) uniform sampler2D texMinDepth;

layout(location=4000) uniform float windowWidth;
layout(location=4001) uniform float windowHeight;

// Attributes
in vec2 pass_TexCoords;

layout(location=0) out vec4 out_Color;

const float MIN_DEPTH_GUARD = 0.000001;

void main() {
    
    // Calculate texture coordinates
    vec2 texCoords = vec2(gl_FragCoord.x / windowWidth, gl_FragCoord.y / windowHeight);

    // Minimum depth control check
    if (useMinDepth)
        if (gl_FragCoord.z < texture(texMinDepth, texCoords).r + MIN_DEPTH_GUARD) discard;

    if (useTexture)
        out_Color = vec4(color * texture(tex, texCoords).xyz, 1);
    else
        out_Color = vec4(color, 1);

}