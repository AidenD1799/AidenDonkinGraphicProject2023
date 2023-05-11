#version 420

layout (location = 0) in vec3 positionVector; //Declaration of layout variables
layout (location = 2) in vec3 normalVector;
layout (location = 1) in vec2 texCoordsVector;

out vert_vars //Declaration of output variables that will be passed to fragment shader
{
    vec2 vertTexCoords;
    vec3 vertNormal;
    vec3 vertPosition;
} vert_out;

uniform mat4 vertModelMatrix; //Declaration of uniform variables, defined in main class
uniform mat4 transform;

void main()
{
    vert_out.vertTexCoords = texCoordsVector;                                        //Passes layout variable data to output variable
    vert_out.vertNormal = mat3(transpose(inverse(vertModelMatrix))) * normalVector;
    vert_out.vertPosition = vec3(vertModelMatrix * vec4(positionVector, 1.0));

    gl_Position = transform * vec4(positionVector, 1.0);    //Sets position 
}  
