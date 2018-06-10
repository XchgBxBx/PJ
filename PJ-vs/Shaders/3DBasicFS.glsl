#version 330

in vec4 Color;
in vec2 UVCoord0;

uniform sampler2D gSampler;

out vec4 FragColor;

void main()
{    
    vec4 texColor = texture2D(gSampler, UVCoord0.xy);

//    FragColor = vec4(texColor.x, texColor.y, texColor.z, 1.0);
    FragColor = vec4(Color.x, Color.y, Color.z, 1.0);

    // DEBUG UVCoord:
    // FragColor = vec4(UVCoord0.x, UVCoord0.y, 0.0, 1.0);
}