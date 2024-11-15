#version 330 core
in vec3 ourColor;
out vec4 FragColor;

void main()
{
    // Debug: Output the color values we're receiving
    FragColor = vec4(ourColor, 1.0);
    
    // Uncomment to verify if shader is being used at all
    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);  // Pure red
}