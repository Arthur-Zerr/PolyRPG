#version 330 core

// Pos
layout (location = 0) in vec3 aPos;

//Normals
layout (location = 1) in vec3 aNormal;

// Color
layout (location = 2) in vec3 aColor;



out vec3 currentPosition;
out vec3 Normal;
out vec3 color;

uniform mat4 camMatrix;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
    currentPosition = vec3(translation * rotation * scale * vec4(aPos, 1.0f));

    gl_Position = camMatrix * vec4(currentPosition, 1.0f);
    Normal = aNormal;
    color = aColor;
}