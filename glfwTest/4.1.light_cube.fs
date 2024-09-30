#version 330 core
uniform sampler2D texture;
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0,0.0,1.0,1.0); // set all 4 vector values to 1.0
}