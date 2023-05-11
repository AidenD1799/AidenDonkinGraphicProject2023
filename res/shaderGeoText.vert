//Version Number
#version 420


uniform mat4 transform; //Declaration of uniform variables, defined in main class


out vec3 vertNormal; //Declaration of output variables that will be passed to fragment shader
out vec4 vertPosition; 

layout (location = 0) in vec3 vertexPosition; //Declaration of layout variables
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 vertexNormal;

out vert_vars //Declaration of output variables that will be passed to geometry shader
{
	vec2 outputTexCoords;

}vert_out;

void main()
{
	
	vertNormal = vertexNormal;					//Passes layout variable data to output variable
	vertPosition = vec4(vertexPosition, 1.0);
	vert_out.outputTexCoords = texCoords;


	
	gl_Position = transform * vec4(vertexPosition, 1.0); //Assigns the current vertex position

}