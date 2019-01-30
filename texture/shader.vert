#version 330
in vec3 VertexPosition;
in vec2 uv;
out vec2 VertexUVCoord;
void main()
{
    VertexUVCoord = uv;
    gl_Position = vec4 (VertexPosition,1.0);
}
