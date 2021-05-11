#version 430

// Uniforms
layout(location=2003) uniform vec3 color;
layout(location=2004) uniform sampler2D tex;
layout(location=3001) uniform bool useTexture;
layout(location=4000) uniform float windowWidth;
layout(location=4001) uniform float windowHeight;

// Attributes
in vec2 pass_TexCoords;

layout(location=0) out vec4 out_Color;

void main() {
    // Calculate texture coordinates
    vec2 texCoords = vec2(gl_FragCoord.x / windowWidth, gl_FragCoord.y / windowHeight);

    if (useTexture)
        out_Color = vec4(color * texture(tex, texCoords).xyz, 1);
    else
        out_Color = vec4(color, 1);

}