#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    TexCoords = aPos;

    mat4 viewRotation = view;
    viewRotation[3] = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    gl_Position = projection * viewRotation * vec4(aPos, 1.0);
} 