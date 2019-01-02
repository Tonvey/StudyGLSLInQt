#version 410
//属性，这个属性用来获取定点位置，具体的顶点值，由C++传值
in vec3 VertexPosition;
//shader主程序
void main()
{
    gl_Position = vec4 (VertexPosition,1.0);
}
