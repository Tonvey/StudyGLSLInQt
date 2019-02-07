#version 330
out vec4 FragColor;
in vec2 VertexUVCoord;
uniform sampler2D MyTexture;
void main()
{
    FragColor = texture(MyTexture,VertexUVCoord);
}
