#version 420 core

out vert_vars //Declaration of output variables that will be passed to fragment shader
{
    vec2 outputTexCoords;
    vec3 swirlPosVector; // Modified vertex position
}vert_out;

layout(location = 0) in vec3 vertPosition; //Declaration of layout variables
layout(location = 1) in vec2 vertTexCoords; 

uniform mat4 model; //Declaration of uniform variables, defined in main class
uniform mat4 view;
uniform mat4 projection;
uniform float swirlSeed; 
uniform float timeVar;
uniform float randomConstant;

float random(float seed) //Used to create a random element in the swirl effect
{
    return fract(sin(seed) * randomConstant ); //Used the defined randomConstant to return a semi-random number
}

void main()
{  
    vec4 transformPosition = model * vec4(vertPosition, 1.0); //Determines position of shader

    vec2 swirledTexCoord = vertTexCoords; //Assigns texture coordinates

    // Creation of swirling effect 
    float swirlIntensity = 2.0; // Determines the intensity of the swirl displayed
    float angle = length(transformPosition.xy) * swirlIntensity +  timeVar * random(swirlSeed); //Adds a random element to the swirl
    mat2 swirlAngleMatrix = mat2(cos(angle), sin(angle), -sin(angle), cos(angle)); //Determines angle of swirl
    vert_out.swirlPosVector = vec3(swirlAngleMatrix * transformPosition.xy, transformPosition.z); // Passes swirl data to output variable

    gl_Position = projection * view * vec4(vert_out.swirlPosVector, 1.0); //Sets current vertext position
    vert_out.outputTexCoords = swirledTexCoord; //Passes the texture coordinate data to the output variable
}

