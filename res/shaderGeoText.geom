//Version number
#version 420 core


in vert_vars //Receives variables from vertex shader
{
    vec2 outputTexCoords;

} geom_in[];

out geom_vars //Declaration of output variables that will be passed to fragment shader
{
    vec2 geomTexCoords; 

}geom_out;

uniform float timeVar; //Declaration of uniform variables, defined in main class

layout (triangles) in; //Declaration of layout variables
layout (triangle_strip, max_vertices = 3) out;

vec4 explode(vec4 position, vec3 normal) //Creates the explosion effect seen in the application
{
    float intensity = 7.0; //Determines magnitude of explosion

    vec3 explodeDirection = normal * ((sin(timeVar) + 1.0) / 2.0) * intensity; //Determines direction of explosion
	
    return position + vec4(explodeDirection, 0.0);//Returns the explosion data
}

vec3 GetNormal() //Returns normalised vector data
{

   vec3 firstVec = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 secondVec = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   
   return normalize(cross(firstVec, secondVec)); //Calculates cross product of created vectors
}

void main()
{

    vec3 normalVector = GetNormal(); //Calculates normal

    gl_Position = explode(gl_in[0].gl_Position, normalVector); //Assigns current vertex positions
    geom_out.geomTexCoords = geom_in[0].outputTexCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normalVector); //Creates explosion 
    geom_out.geomTexCoords = geom_in[1].outputTexCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normalVector);
    geom_out.geomTexCoords = geom_in[2].outputTexCoords;
    EmitVertex();
    EndPrimitive();
}  