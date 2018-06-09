#version 330

// in vec4 Color;
in vec2 UVCoord0;

uniform sampler2D gSampler;

out vec4 FragColor;

void main()
{    
    FragColor = texture2D(gSampler, UVCoord0.xy);

    // DEBUG UVCoord:
    // FragColor = vec4(UVCoord0.x, UVCoord0.y, 0.0, 1.0);
}