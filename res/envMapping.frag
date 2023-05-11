#version 420

out vec4 fragColour; //Resultant colour of shader

in vert_vars //Receives variables from vertex shader
{
    vec2 vertTexCoords;
    vec3 vertNormal;
    vec3 vertPosition;
} frag_in;

uniform vec3 cameraPositionVector; //Declaration of uniform variables, defined in main class
uniform samplerCube skyboxVar;

layout(binding = 1) uniform sampler2D diffuse; //Declaration of layout variables

void main()
{
    vec3 incidentVector = normalize(frag_in.vertPosition - cameraPositionVector); // Normalises incident vector

    vec3 reflectionVector = reflect(incidentVector, normalize(frag_in.vertNormal)); // Calculate the reflection vector
    
    vec4 envColour = vec4(texture(skyboxVar, reflectionVector).rgb, 1.0); //Determines the environment colour

    vec4 diffuseColour = texture2D(diffuse, frag_in.vertTexCoords); //Creates the diffuse colour

    float colourMixVariable = 0.65f; //Declares the variable used to mix encironment and diffuse colours

    colourMixVariable = clamp(colourMixVariable, 0.0, 1.0); //Clamps mix variable

    vec4 outputColour = mix(diffuseColour, envColour, colourMixVariable); //Calculates output colour

    fragColour = outputColour; //Assigns output colour to frag colour 
}