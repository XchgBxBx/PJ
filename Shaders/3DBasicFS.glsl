#version 330

in vec4 Color;
out vec4 FragColor;


void main()
{
    FragColor = Color;
    //FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}