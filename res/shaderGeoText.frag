//Version number
#version 420


 in geom_vars //Receives variables from geometry shader
 {
	vec2 geomTexCoords;

 }frag_in;


layout( location = 0 ) out vec4 fragcolor; //Declaration of layout variables

uniform sampler2D diffuseVar; //Declaration of uniform variables, defined in main class


void main()
{
	vec4 outputColour;
	
	outputColour = texture2D(diffuseVar, frag_in.geomTexCoords); //Determines output colour
    fragcolor = outputColour; //Outputs final colour
}