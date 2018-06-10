#version 330

layout (location = 0) in vec3  Position;
layout (location = 1) in vec2  UVCoord;
layout (location = 2) in ivec3 BoneIDs;
layout (location = 3) in vec3  Weights;

uniform mat4 gWorld;
uniform mat4 gProjView;

out vec4 Color;
out vec2 UVCoord0;

void main()
{
    gl_Position = gProjView * gWorld * vec4(
        Position.x,
        Position.y,
        Position.z,
        1.0
    );

    //Color = vec4(clamp(Position, 0.0, 1.0), 1.0);

//    DEBUG UV COORD:
//    Color = vec4(UVCoord.x, UVCoord.y, 0.0, 1.0);

//    DEBUG BONE ID:
    Color = vec4(BoneIDs.x * Weights.x, BoneIDs.y * Weights.y, BoneIDs.z * Weights.z, 1.0);

    UVCoord0 = UVCoord;
}