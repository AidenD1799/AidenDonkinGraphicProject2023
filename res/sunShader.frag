#version 420 core

in vert_vars //Receives variables from vertex shader
{
    vec2 outputTexCoords;
    vec3 swirlPosVector;
}frag_in;

out vec4 fragColor;

uniform sampler2D textureSamplerVar; //Declaration of uniform variables, defined in main class
uniform float timeVarFrag; // Time value in seconds
uniform float minBI; // Minimum bloom intensity
uniform float maxBI; // Maximum bloom intensity
uniform float bFrequency; // Frequency of bloom intensity modulation

const int blurEffectRadius = 6; // Adjust the blur radius to control the size of the blur

void main()
{
    vec4 textureColour = texture(textureSamplerVar, frag_in.outputTexCoords); //Assigns data from texture sample
    
    float currentBI = mix(minBI, maxBI, 0.5 + 0.5 * sin(timeVarFrag * bFrequency)); //Determines the intensity of the bloom effect
    
    vec3 bloomEffectColour = vec3(0.0); //Creates a colour for the bloom effect

    for (int x = -blurEffectRadius; x <= blurEffectRadius; x++) //For loop used to create bloom colour from offset vector, texture coordinates, and texture sample
    {
        for (int y = -blurEffectRadius; y <= blurEffectRadius; y++)
        {
            vec2 offsetVector = vec2(x, y);
            vec4 bloomEffectSample = texture(textureSamplerVar, frag_in.outputTexCoords + offsetVector / textureSize(textureSamplerVar, 0));
            bloomEffectColour += bloomEffectSample.rgb;
         }
     }

    bloomEffectColour /= float((blurEffectRadius * 2 + 1) * (blurEffectRadius * 2 + 1)); //Refines bloom colour based on blur effect radius
    bloomEffectColour *= currentBI; //Applies bloom intensity variable to created colour
    
    
    vec3 outputColour = textureColour.rgb + bloomEffectColour; //Combines the texture colour with the created bloom colour
    fragColor = vec4(outputColour, 1.0); //Outputs the frag colour
}