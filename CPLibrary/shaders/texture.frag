#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 inputColor;
uniform sampler2D ourTexture;

void main()
{
    FragColor = inputColor / 255 * texture(ourTexture, TexCoord);
}