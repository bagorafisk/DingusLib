#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);
    // Debug: Pass through color exactly as received
    ourColor = aColor;
    
    // Uncomment to verify color pipeline
    // ourColor = vec3(1.0, 1.0, 1.0);  // Pure white
}